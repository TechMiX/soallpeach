#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <pthread.h>

int s, sum;
pthread_mutex_t lock;

void* process_request(int cs) {

    int r, i = 0;
    char buf[1024];

    memset(&buf, 0, sizeof(buf));

    do
        r = read(cs, buf, 1023);
    while (r < 1 && ++i < 1000);

    if (buf[0] == 0) {
        close(cs);
        return NULL;
    }

    // -> ENDPOINT /count

    if (buf[5] == 'c') {
        char sum_string[128];
        memset(&sum_string, 0, sizeof(sum_string));
        pthread_mutex_lock(&lock);
        r = snprintf(sum_string, 128, "%d", sum);
        pthread_mutex_unlock(&lock);
        r = write(cs, sum_string, 128);
        close(cs);
        return NULL;
    }

    // -> ENDPOINT /

    close(cs);

    // seek buffer to the start of body
    char* bufp = buf;
    do
        while (*bufp++ != '\r')
            continue;
    while (*++bufp != '\r');

    // atoi body
    int n = 0;
    while (1)
        if (*bufp > '\r') {
            n = (n << 1) + (n << 3) + *bufp++ - '0';
            continue;
        } else if (*bufp++ == 0)
            break;

    pthread_mutex_lock(&lock);
    sum += n;
    pthread_mutex_unlock(&lock);

    return NULL;
}

void* request_thread(void* vars) {
    return process_request( *((int*) vars) );
}

void SIGINT_handler(int sig) {
    pthread_exit(NULL);
    pthread_mutex_destroy(&lock);
    close(s);
    exit(0);
}

int main() {

    signal(SIGINT, SIGINT_handler);

    int cl;
    struct sockaddr_in srv;

    s = socket(AF_INET, SOCK_STREAM, 0);
    srv.sin_family = AF_INET;
    srv.sin_addr.s_addr = htonl(INADDR_ANY);
    srv.sin_port = htons(80);
    cl = sizeof(srv);

    bind(s, (struct sockaddr*) &srv, cl);
    listen(s, 1000000);

    pthread_mutex_init(&lock, NULL);

    while (1) {
        pthread_t tid;
        int cs = accept(s, (struct sockaddr*) &srv, &cl);
        pthread_create(&tid, NULL, request_thread, (void*) &cs);
    }

    return 0;
}

