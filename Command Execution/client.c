#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char cmd[100], result[1024];

    // 1. Create TCP socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // 2. Configure server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // 3. Connect to server
    connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // 4. Input command
    printf("Enter command: ");
    fgets(cmd, sizeof(cmd), stdin);
    cmd[strcspn(cmd, "\n")] = 0;

    // 5. Send command
    write(client_socket, cmd, strlen(cmd));

    // 6. Receive result
    memset(result, 0, sizeof(result));
    read(client_socket, result, sizeof(result));

    printf("Command Output:\n%s\n", result);

    close(client_socket);

    return 0;
}
