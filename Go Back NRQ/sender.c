/* sender.c */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

int main() {
    int sock, n, window, base = 1;
    struct sockaddr_in server;
    char frame[100], ack[100];

    /* create socket */
    sock = socket(AF_INET, SOCK_STREAM, 0);

    /* server details */
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;

    /* connect */
    connect(sock, (struct sockaddr *)&server, sizeof(server));

    printf("Enter total frames: ");
    scanf("%d", &n);

    printf("Enter window size: ");
    scanf("%d", &window);

    while (base <= n) {

        int end = base + window - 1;
        if (end > n)
            end = n;

        printf("\nSending frames: ");

        /* send window frames */
        for (int i = base; i <= end; i++) {
            sprintf(frame, "Frame %d", i);
            write(sock, frame, strlen(frame));
            printf("%d ", i);
        }

        printf("\n");

        int success = 1;

        /* wait ACK for all frames */
        for (int i = base; i <= end; i++) {

            fd_set set;
            struct timeval timeout;

            FD_ZERO(&set);
            FD_SET(sock, &set);

            timeout.tv_sec = 3;
            timeout.tv_usec = 0;

            int rv = select(sock + 1, &set, NULL, NULL, &timeout);

            if (rv == 1) {
                memset(ack, 0, sizeof(ack));
                read(sock, ack, sizeof(ack));
                printf("ACK received for Frame %d\n", i);
            } else {
                printf("Timeout at Frame %d\n", i);
                printf("Go-Back-N: Resending from Frame %d\n", i);
                base = i;
                success = 0;
                break;
            }
        }

        if (success)
            base = end + 1;
    }

    strcpy(frame, "END");
    write(sock, frame, strlen(frame));

    close(sock);

    return 0;
}
