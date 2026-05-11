#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr;
    char buffer[1024];
    FILE *fp;

    // 1. Create TCP socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // 2. Configure server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // 3. Bind
    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // 4. Listen
    listen(server_socket, 1);

    printf("Server waiting for file...\n");

    // 5. Accept client
    client_socket = accept(server_socket, NULL, NULL);

    // 6. Open file to save received data
    fp = fopen("received.txt", "w");

    // 7. Receive file data
    while (read(client_socket, buffer, sizeof(buffer)) > 0) {
        fputs(buffer, fp);
        memset(buffer, 0, sizeof(buffer));
    }

    printf("File received successfully\n");

    fclose(fp);
    close(client_socket);
    close(server_socket);

    return 0;
}
