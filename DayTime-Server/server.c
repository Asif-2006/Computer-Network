#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr;
    char datetime[100];
    time_t now;

    // Create TCP socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Configure server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // Listen
    listen(server_socket, 1);

    printf("DateTime Server waiting...\n");

    // Accept client
    client_socket = accept(server_socket, NULL, NULL);

    // Get current time
    now = time(NULL);

    // Convert to readable format
    snprintf(datetime, sizeof(datetime), "%s", ctime(&now));

    // Send to client
    send(client_socket, datetime, strlen(datetime), 0);

    close(client_socket);
    close(server_socket);

    return 0;
}
