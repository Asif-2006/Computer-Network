#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int s, c;
    struct sockaddr_in a;
    char msg[100];

    // create socket
    s = socket(AF_INET, SOCK_STREAM, 0);

    // setup address
    a.sin_family = AF_INET;
    a.sin_port = htons(8080);
    a.sin_addr.s_addr = INADDR_ANY;

    // bind + listen
    bind(s, (struct sockaddr*)&a, sizeof(a));
    listen(s, 1);

    printf("Receiver waiting...\n");

    // accept sender
    c = accept(s, NULL, NULL);

    // receive message
    read(c, msg, sizeof(msg));

    printf("Message received: %s\n", msg);

    close(c);
    close(s);

    return 0;
}
