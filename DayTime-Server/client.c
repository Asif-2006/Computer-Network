#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char msg[100];

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Configure server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Connect to server
    connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // Receive datetime
    memset(msg, 0, sizeof(msg));
    recv(client_socket, msg, sizeof(msg), 0);

    printf("Current Date and Time: %s", msg);

    close(client_socket);

    return 0;
}
