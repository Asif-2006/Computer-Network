#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char msg[] = "Hello from UDP Client";
    char reply[100];
    socklen_t len = sizeof(server_addr);

    // Create UDP socket
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);

    // Configure server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Send message
    sendto(client_socket, msg, strlen(msg), 0,
           (struct sockaddr*)&server_addr, len);

    // Receive reply
    recvfrom(client_socket, reply, sizeof(reply), 0,
             NULL, NULL);

    printf("Message from server: %s\n", reply);

    close(client_socket);

    return 0;
}
