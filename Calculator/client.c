#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char data[100];
    float a, b;
    char op;

    // 1. Create TCP socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // 2. Configure server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // 3. Connect
    connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // 4. Input
    printf("Enter expression (example: 10 + 5): ");
    scanf("%f %c %f", &a, &op, &b);

    // 5. Send data
    sprintf(data, "%f %c %f", a, op, b);
    write(client_socket, data, strlen(data));

    // 6. Receive result
    memset(data, 0, sizeof(data));
    read(client_socket, data, sizeof(data));

    printf("Result = %s\n", data);

    close(client_socket);

    return 0;
}
