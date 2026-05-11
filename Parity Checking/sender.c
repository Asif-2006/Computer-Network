/* sender.c - Parity Check */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int countOnes(char s[]) {
    int count = 0;
    for (int i = 0; s[i]; i++)
        if (s[i] == '1')
            count++;
    return count;
}

int main() {
    int s, choice;
    struct sockaddr_in a;
    char msg[100];

    s = socket(AF_INET, SOCK_STREAM, 0);

    a.sin_family = AF_INET;
    a.sin_port = htons(8080);
    a.sin_addr.s_addr = INADDR_ANY;

    connect(s, (struct sockaddr*)&a, sizeof(a));

    printf("Enter binary data: ");
    scanf("%s", msg);

    /* add parity bit */
    if (countOnes(msg) % 2 == 0)
        strcat(msg, "0");
    else
        strcat(msg, "1");

    printf("Introduce error? (1=yes 0=no): ");
    scanf("%d", &choice);

    if (choice == 1)
        msg[0] = (msg[0] == '0') ? '1' : '0';

    write(s, msg, strlen(msg));

    printf("Sent Data: %s\n", msg);

    close(s);
}
