/* receiver.c */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int s, c;
    struct sockaddr_in a;
    char msg[100];

    s = socket(AF_INET, SOCK_STREAM, 0);

    a.sin_family = AF_INET;
    a.sin_port = htons(8080);
    a.sin_addr.s_addr = INADDR_ANY;

    bind(s, (struct sockaddr*)&a, sizeof(a));
    listen(s, 1);

    printf("Receiver waiting...\n");

    c = accept(s, NULL, NULL);

    read(c, msg, sizeof(msg));

    printf("Received Data: %s\n", msg);

    if (msg[strlen(msg)-1] == '0')
        printf("No Error Detected\n");
    else
        printf("Error Detected\n");

    close(c);
    close(s);
}
