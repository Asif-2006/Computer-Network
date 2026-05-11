#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr;
    char msg[100];

    // 1. Create TCP socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // 2. Set server address details
    server_addr.sin_family = AF_INET;           // IPv4
    server_addr.sin_port = htons(8080);         // Port number
    server_addr.sin_addr.s_addr = INADDR_ANY;   // Accept from any IP

    // 3. Bind socket to address and port
    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // 4. Listen for incoming client connection
    listen(server_socket, 1);

    printf("Echo Server waiting...\n");

    // 5. Accept client connection
    client_socket = accept(server_socket, NULL, NULL);

    // 6. Receive message from client
    memset(msg, 0, sizeof(msg));
    read(client_socket, msg, sizeof(msg));

    printf("Received from client: %s\n", msg);

    // 7. Send same message back to client (echo)
    write(client_socket, msg, strlen(msg));

    // 8. Close sockets
    close(client_socket);
    close(server_socket);

    return 0;
}
