#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

int main() {
    int sock;
    struct sockaddr_in server_addr;
    struct hostent *server;
    char request[200];
    char response[1024];
    char host[] = "example.com";

    // 1. DNS lookup
    server = gethostbyname(host);

    // 2. Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // 3. Configure server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80);
    memcpy(&server_addr.sin_addr.s_addr,
           server->h_addr,
           server->h_length);

    // 4. Connect to web server
    connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // 5. Create HTTP GET request
    sprintf(request,
            "GET / HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n",
            host);

    // 6. Send request
    write(sock, request, strlen(request));

    // 7. Receive response
    while (read(sock, response, sizeof(response)-1) > 0) {
        printf("%s", response);
        memset(response, 0, sizeof(response));
    }

    close(sock);

    return 0;
}
