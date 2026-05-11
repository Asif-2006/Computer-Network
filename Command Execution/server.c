#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr;
    char cmd[100], output[1024];
    FILE *fp;

    // 1. Create TCP socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // 2. Configure server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // 3. Bind socket
    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // 4. Listen
    listen(server_socket, 1);

    printf("Server waiting...\n");

    // 5. Accept client
    client_socket = accept(server_socket, NULL, NULL);

    // 6. Receive command
    memset(cmd, 0, sizeof(cmd));
    read(client_socket, cmd, sizeof(cmd));

    printf("Command received: %s\n", cmd);

    // 7. Execute command
    fp = popen(cmd, "r");

    memset(output, 0, sizeof(output));

    while (fgets(output + strlen(output),
                 sizeof(output) - strlen(output), fp) != NULL);

    pclose(fp);

    // 8. Send output to client
    write(client_socket, output, strlen(output));

    close(client_socket);
    close(server_socket);

    return 0;
}
