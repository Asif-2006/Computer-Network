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

    // Bind
    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // Listen
    listen(server_socket, 1);

    printf("Server waiting...\n");

    // Accept client
    client_socket = accept(server_socket, NULL, NULL);

    while (1) {
        memset(msg, 0, sizeof(msg));

        // Receive from client
        read(client_socket, msg, sizeof(msg));

        if (strcmp(msg, "exit") == 0)
            break;

        printf("Client: %s\n", msg);

        // Send reply
        printf("Server: ");
        fgets(msg, sizeof(msg), stdin);
        msg[strcspn(msg, "\n")] = 0;

        write(client_socket, msg, strlen(msg));

        if (strcmp(msg, "exit") == 0)
            break;
    }

    close(client_socket);
    close(server_socket);

    return 0;
}
