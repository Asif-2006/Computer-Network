#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char msg[] = "Hello from Client";
    char reply[100];

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Connect to server
    connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // Send message
    write(client_socket, msg, strlen(msg));

    // Receive reply
    read(client_socket, reply, sizeof(reply));

    printf("Message from server: %s\n", reply);

    close(client_socket);

    return 0;
}
