#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr;
    char msg[100];

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Configure server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // Listen for client
    listen(server_socket, 1);

    printf("Server waiting for connection...\n");

    // Accept client
    client_socket = accept(server_socket, NULL, NULL);

    // Receive message
    read(client_socket, msg, sizeof(msg));

    printf("Message from client: %s\n", msg);

    // Send reply
    char reply[] = "Hello from Server";
    write(client_socket, reply, strlen(reply));

    close(client_socket);
    close(server_socket);

    return 0;
}
