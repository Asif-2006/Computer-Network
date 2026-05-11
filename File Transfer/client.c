#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[1024];
    FILE *fp;

    // 1. Create TCP socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // 2. Configure server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // 3. Connect to server
    connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // 4. Open file to send
    fp = fopen("send.txt", "r");

    if (fp == NULL) {
        printf("File not found\n");
        return 1;
    }

    // 5. Send file data
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        write(client_socket, buffer, strlen(buffer));
    }

    printf("File sent successfully\n");

    fclose(fp);
    close(client_socket);

    return 0;
}
