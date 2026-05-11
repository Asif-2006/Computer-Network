#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>

int main() {
    char domain[100];
    struct hostent *host;
    struct in_addr addr;

    // Input domain name
    printf("Enter domain name: ");
    scanf("%s", domain);

    // DNS lookup
    host = gethostbyname(domain);

    if (host == NULL) {
        printf("DNS lookup failed\n");
        return 1;
    }

    // Convert address
    addr = *(struct in_addr *)host->h_addr;

    printf("IP Address: %s\n", inet_ntoa(addr));

    return 0;
}
