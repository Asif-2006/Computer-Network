#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n, window;

    printf("Enter total frames: ");
    scanf("%d", &n);

    printf("Enter window size: ");
    scanf("%d", &window);

    int received[100] = {0};  // track received frames

    srand(time(0));

    int remaining = n;

    while (remaining > 0) {

        printf("\nSending frames: ");

        for (int i = 1; i <= n; i++) {
            if (received[i] == 0) {
                printf("%d ", i);
            }
        }
        printf("\n");

        // simulate each frame
        for (int i = 1; i <= n; i++) {

            if (received[i] == 0) {

                int success = rand() % 2;

                if (success) {
                    printf("Frame %d received\n", i);
                    received[i] = 1;
                    remaining--;
                } else {
                    printf("Frame %d lost\n", i);
                }
            }
        }
    }

    printf("\nAll frames sent successfully!\n");

    return 0;
}
