#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

int s;

void SIGINT_handler(int sig) {
    close(s);
    exit(0);
}

int main() {

    int cs, cl, r, n, i, sum = 0;
    char buf[1024], sum_string[128], http_200_ok[] = "HTTP/1.1 200 OK\r\n\r\n";
    char* bufp = buf;
    struct sockaddr_in srv;

    signal(SIGINT, SIGINT_handler);

    s = socket(AF_INET, SOCK_STREAM, 0);

    srv.sin_family = AF_INET;
    srv.sin_addr.s_addr = htonl(INADDR_ANY);
    srv.sin_port = htons(80);
    cl = sizeof(srv);

    bind(s, (struct sockaddr*) &srv, cl);
    listen(s, 1000000);

    memset(&sum_string, 0, sizeof(sum_string));

    while (1) {

        memset(&buf, 0, sizeof(buf));
        do
            cs = accept(s, (struct sockaddr*) &srv, &cl);
        while (cs < 1);

        i = 0;
        do
            r = read(cs, buf, 1023);
        while (r < 1 && ++i < 1000);

        if (buf[0] == 0) {
            close(cs);
            continue;
        }

        // -> ENDPOINT /count

        if (buf[5] == 'c') {
            r = snprintf(sum_string, 128, "%d", sum);
            r = write(cs, sum_string, 128);
            close(cs);
            continue;
        }

        // -> ENDPOINT /

        r = write(cs, http_200_ok, 20);
        close(cs);

        // seek buffer to the start of body
        bufp = buf;
        do
            while (*bufp++ != '\r')
                continue;
        while (*++bufp != '\r');

        // atoi body
        n = 0;
        while (1)
            if (*bufp > '\r') {
                n = (n << 1) + (n << 3) + *bufp++ - '0';
                continue;
            } else if (*bufp++ == 0)
                break;

        sum += n;
   }

   return 0;
}

