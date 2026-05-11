#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char msg[100], reply[100];

    // 1. Create TCP socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // 2. Set server details
    server_addr.sin_family = AF_INET;           // IPv4
    server_addr.sin_port = htons(8080);         // Same port as server
    server_addr.sin_addr.s_addr = INADDR_ANY;   // Local machine

    // 3. Connect to server
    connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // 4. Take message input
    printf("Enter message: ");
    scanf("%s", msg);

    // 5. Send message to server
    write(client_socket, msg, strlen(msg));

    // 6. Receive echoed message
    memset(reply, 0, sizeof(reply));
    read(client_socket, reply, sizeof(reply));

    printf("Echo from server: %s\n", reply);

    // 7. Close socket
    close(client_socket);

    return 0;
}
