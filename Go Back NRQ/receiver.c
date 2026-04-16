/* receiver.c */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    char frame[100], ack[100];

    srand(time(0));

    /* create socket */
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    /* set address */
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    address.sin_addr.s_addr = INADDR_ANY;

    /* bind */
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    /* listen */
    listen(server_fd, 1);

    printf("Receiver waiting...\n");

    /* accept connection */
    client_fd = accept(server_fd, NULL, NULL);

    while (1) {

        memset(frame, 0, sizeof(frame));
        read(client_fd, frame, sizeof(frame));

        if (strcmp(frame, "END") == 0)
            break;

        printf("Received: %s\n", frame);

        /* random frame loss */
        int x = rand() % 3;

        if (x == 0) {
            printf("Frame lost! No ACK sent\n\n");
        } else {
            strcpy(ack, "ACK");
            write(client_fd, ack, strlen(ack));
            printf("ACK sent\n\n");
        }
    }

    close(client_fd);
    close(server_fd);

    return 0;
}
