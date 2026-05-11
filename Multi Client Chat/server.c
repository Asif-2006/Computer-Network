#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

void *chat(void *arg) {
    int client = *(int *)arg;
    char msg[100];

    while (1) {
        memset(msg, 0, sizeof(msg));
        read(client, msg, sizeof(msg));

        if (strcmp(msg, "exit") == 0)
            break;

        printf("Client: %s\n", msg);
    }

    close(client);
    return NULL;
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr;
    pthread_t t;

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Configure server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind
    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // Listen
    listen(server_socket, 5);

    printf("Multi-client server waiting...\n");

    while (1) {
        // Accept clients
        client_socket = accept(server_socket, NULL, NULL);

        // Create thread for each client
        pthread_create(&t, NULL, chat, &client_socket);
    }

    close(server_socket);

    return 0;
}
