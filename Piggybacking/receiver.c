/* receiver.c - Piggybacking */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int s, c, n;
    struct sockaddr_in a;
    char msg[100], reply[100];

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

        printf("Received Frame %d from Sender\n", n);

        /* send own data + ACK together */
        sprintf(reply, "Frame %d + ACK %d", n + 1, n);
        write(c, reply, strlen(reply));
    }

    close(c);
    close(s);
}
