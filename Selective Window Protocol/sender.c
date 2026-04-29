/* sender.c - Selective Repeat ARQ (stable demo) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

int main() {
    int s, i, n, left;
    struct sockaddr_in a;
    char msg[100], ack[100];
    int done[100] = {0};

    s = socket(AF_INET, SOCK_STREAM, 0);

    a.sin_family = AF_INET;
    a.sin_port = htons(8080);
    a.sin_addr.s_addr = INADDR_ANY;

    connect(s, (struct sockaddr*)&a, sizeof(a));

    printf("Enter number of frames: ");
    scanf("%d", &n);

    left = n;

    while (left > 0) {

        /* send only missing frames */
        for (i = 1; i <= n; i++) {
            if (!done[i]) {
                sprintf(msg, "%d", i);
                write(s, msg, strlen(msg));
                printf("Sent Frame %d\n", i);
                usleep(300000);
            }
        }

        while (1) {

            fd_set set;
            struct timeval t;

            FD_ZERO(&set);
            FD_SET(s, &set);

            t.tv_sec = 2;
            t.tv_usec = 0;

            if (select(s + 1, &set, NULL, NULL, &t) <= 0)
                break;

            memset(ack, 0, sizeof(ack));
            read(s, ack, sizeof(ack));

            int x = atoi(ack);

            if (!done[x]) {
                done[x] = 1;
                left--;
                printf("ACK %d received\n", x);
            }
        }

        printf("Resending only lost frames...\n\n");
    }

    strcpy(msg, "END");
    write(s, msg, strlen(msg));

    close(s);
}
