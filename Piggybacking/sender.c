/* sender.c - Piggybacking */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int s, n, i;
    struct sockaddr_in a;
    char msg[100], reply[100];

    s = socket(AF_INET, SOCK_STREAM, 0);

    a.sin_family = AF_INET;
    a.sin_port = htons(8080);
    a.sin_addr.s_addr = INADDR_ANY;

    connect(s, (struct sockaddr*)&a, sizeof(a));

    printf("Enter number of frames: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {

        sprintf(msg, "%d", i);
        write(s, msg, strlen(msg));

        printf("Sent Frame %d\n", i);

        memset(reply, 0, sizeof(reply));
        read(s, reply, sizeof(reply));

        printf("Received: %s\n", reply);
        sleep(1);
    }

    strcpy(msg, "END");
    write(s, msg, strlen(msg));

    close(s);
}
