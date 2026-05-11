#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_socket;
    struct sockaddr_in server_addr, client_addr;
    char msg[100];
    socklen_t len = sizeof(client_addr);

    // Create UDP socket
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);

    // Configure server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    printf("UDP Server waiting...\n");

    // Receive message
    recvfrom(server_socket, msg, sizeof(msg), 0,
             (struct sockaddr*)&client_addr, &len);

    printf("Message from client: %s\n", msg);

    // Send reply
    char reply[] = "Hello from UDP Server";

    sendto(server_socket, reply, strlen(reply), 0,
           (struct sockaddr*)&client_addr, len);

    close(server_socket);

    return 0;
}
