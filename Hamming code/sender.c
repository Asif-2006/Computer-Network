/* sender.c - Hamming Code */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int s, choice;
    struct sockaddr_in a;
    char msg[100];

    s = socket(AF_INET, SOCK_STREAM, 0);

    a.sin_family = AF_INET;
    a.sin_port = htons(8080);
    a.sin_addr.s_addr = INADDR_ANY;

    connect(s, (struct sockaddr*)&a, sizeof(a));

    printf("Enter 7-bit Hamming code: ");
    scanf("%s", msg);

    printf("Introduce error? (1=yes 0=no): ");
    scanf("%d", &choice);

    if (choice == 1)
        msg[2] = (msg[2] == '0') ? '1' : '0';

    write(s, msg, strlen(msg));

    printf("Sent Data: %s\n", msg);

    close(s);
}
