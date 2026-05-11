/* receiver.c - Hamming Code */
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

    int p1 = (msg[0]-'0') ^ (msg[2]-'0') ^ (msg[4]-'0') ^ (msg[6]-'0');
    int p2 = (msg[1]-'0') ^ (msg[2]-'0') ^ (msg[5]-'0') ^ (msg[6]-'0');
    int p4 = (msg[3]-'0') ^ (msg[4]-'0') ^ (msg[5]-'0') ^ (msg[6]-'0');

    int error = p4*4 + p2*2 + p1;

    if (error == 0)
        printf("No Error Detected\n");
    else
        printf("Error at position %d\n", error);

    close(c);
    close(s);
}
