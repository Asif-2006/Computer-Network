#include <stdio.h>

int main() {
    int n, window;

    printf("Enter total frames: ");
    scanf("%d", &n);

    printf("Enter window size: ");
    scanf("%d", &window);

    int i = 1;

    while (i <= n) {

        printf("\nCurrent Window: ");

        for (int j = i; j < i + window && j <= n; j++) {
            printf("%d ", j);
        }

        printf("\nSending frames...\n");

        printf("ACK received for Frame %d\n", i);

        i++;  // slide window
    }

    return 0;
}
