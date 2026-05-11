#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock, port;
    struct sockaddr_in target;
    char ip[50];

    // Input target IP
    printf("Enter target IP: ");
    scanf("%s", ip);

    // Scan ports 1 to 10000
    for (port = 1; port <= 10000; port++) {

        // Create socket
        sock = socket(AF_INET, SOCK_STREAM, 0);

        target.sin_family = AF_INET;
        target.sin_port = htons(port);
        inet_pton(AF_INET, ip, &target.sin_addr);

        // Try connection
        if (connect(sock, (struct sockaddr*)&target, sizeof(target)) == 0) {
            printf("Port %d is OPEN\n", port);
        }

        close(sock);
    }

    return 0;
}
