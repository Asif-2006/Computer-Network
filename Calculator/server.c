#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr;
    char data[100];
    float a, b, result;
    char op;

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

    printf("Calculator Server waiting...\n");

    // 5. Accept client
    client_socket = accept(server_socket, NULL, NULL);

    // 6. Receive data
    read(client_socket, data, sizeof(data));

    // Format: number operator number
    sscanf(data, "%f %c %f", &a, &op, &b);

    // 7. Perform calculation
    switch(op) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/': result = a / b; break;
        default: result = 0;
    }

    // 8. Send result
    sprintf(data, "%.2f", result);
    write(client_socket, data, strlen(data));

    close(client_socket);
    close(server_socket);

    return 0;
}
