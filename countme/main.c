#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>

int main(){

    int s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_input_addr;

    serv_input_addr.sin_family = AF_INET;
    serv_input_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_input_addr.sin_port = htons(80);

    bind(s, (struct sockaddr*)&serv_input_addr, sizeof(serv_input_addr));
    listen(s, 100000);

    int cs, r, n, sum = 0;
    int client_length = sizeof(serv_input_addr);
    char buf[1024], sum_string[128];
    char* bufp = buf;

    memset(&sum_string, 0, sizeof(sum_string));

    while(1) {
        memset(&buf, 0, sizeof(buf));
        cs = accept(s, (struct sockaddr*) &serv_input_addr, &client_length);
        r = read(cs, buf, 1023);

        // -> ENDPINT /count

        if (buf[5] == 'c') {
            r = snprintf(sum_string, 128, "%d", sum);
            r = write(cs, sum_string, 128);
            close(cs);
            continue;
        }

        // -> ENDPOINT /

        close(cs);

        // seek buffer to the start of body
        bufp = buf;
        do
            while (*bufp++ != '\r')
                continue;
        while (*++bufp != '\r');

        // fgets and atoi body
        n = 0;
        while (1)
            if (*bufp > '\r') {
                n = (n << 1) + (n << 3) + *bufp++ - '0';
                continue;
            } else if (*bufp++ == 0)
                break;

        sum += n;
   }

   close(s);

   return 0;
}

