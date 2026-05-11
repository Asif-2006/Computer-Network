#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int s;
    struct sockaddr_in a;
    char msg[] = "Hello from Sender";

    // create socket
    s = socket(AF_INET, SOCK_STREAM, 0);

    // setup receiver address
    a.sin_family = AF_INET;
    a.sin_port = htons(8080);
    a.sin_addr.s_addr = INADDR_ANY;

    // connect to receiver
    connect(s, (struct sockaddr*)&a, sizeof(a));

    // send message
    write(s, msg, strlen(msg));

    printf("Message sent\n");

    close(s);

    return 0;
}
