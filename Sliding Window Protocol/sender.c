/* sender.c - Sliding Window */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int s, n, w, base = 1, i;
    struct sockaddr_in a;
    char msg[100], ack[100];

    s = socket(AF_INET, SOCK_STREAM, 0);

    a.sin_family = AF_INET;
    a.sin_port = htons(8080);
    a.sin_addr.s_addr = INADDR_ANY;

    connect(s, (struct sockaddr*)&a, sizeof(a));

    printf("Enter total frames: ");
    scanf("%d", &n);

    printf("Enter window size: ");
    scanf("%d", &w);

    while (base <= n) {

        printf("\nCurrent Window: ");

        for (i = base; i < base + w && i <= n; i++) {
            printf("%d ", i);

            sprintf(msg, "%d", i);
            write(s, msg, strlen(msg));

            memset(ack, 0, sizeof(ack));
            read(s, ack, sizeof(ack));
        }

        printf("\nWindow Slid Forward\n");

        base++;
        sleep(1);
    }

    strcpy(msg, "END");
    write(s, msg, strlen(msg));

    close(s);
}
