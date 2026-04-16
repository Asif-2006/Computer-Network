/* sender.c */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

int main() {
    int sock, n, i = 1;
    struct sockaddr_in server;
    char frame[100], ack[100];

    /* create socket */
    sock = socket(AF_INET, SOCK_STREAM, 0);

    /* set server details */
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;

    /* connect */
    connect(sock, (struct sockaddr *)&server, sizeof(server));

    printf("Enter number of frames: ");
    scanf("%d", &n);

    while (i <= n) {

        sprintf(frame, "Frame %d", i);

        /* send frame */
        write(sock, frame, strlen(frame));
        printf("Sent: %s\n", frame);

        /* wait for ACK with timeout */
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
            printf("ACK received for Frame %d\n\n", i);
            i++;
        } else {
            printf("Timeout! Resending Frame %d\n\n", i);
        }
    }

    /* end signal */
    strcpy(frame, "END");
    write(sock, frame, strlen(frame));

    close(sock);

    return 0;
}
