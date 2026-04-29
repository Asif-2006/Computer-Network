/* receiver.c  - Selective Repeat ARQ (stable demo) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int s, c, n;
    struct sockaddr_in a;
    char msg[100], ack[100];
    int lost_once[100] = {0};   // frame will fail only first time

    s = socket(AF_INET, SOCK_STREAM, 0);

    a.sin_family = AF_INET;
    a.sin_port = htons(8080);
    a.sin_addr.s_addr = INADDR_ANY;

    bind(s, (struct sockaddr*)&a, sizeof(a));
    listen(s, 1);

    printf("Receiver waiting...\n");

    c = accept(s, NULL, NULL);

    while (1) {

        memset(msg, 0, sizeof(msg));
        read(c, msg, sizeof(msg));

        if (strcmp(msg, "END") == 0)
            break;

        sscanf(msg, "%d", &n);

        /* fail frame 3 only first time */
        if (n == 3 && lost_once[3] == 0) {
            printf("Frame %d lost\n", n);
            lost_once[3] = 1;
        }
        else {
            printf("Frame %d received\n", n);

            sprintf(ack, "%d", n);
            write(c, ack, strlen(ack));
        }
    }

    close(c);
    close(s);
}
