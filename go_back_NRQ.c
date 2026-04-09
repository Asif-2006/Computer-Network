#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n, window, i = 1;

    printf("Enter total frames: ");
    scanf("%d", &n);

    printf("Enter window size: ");
    scanf("%d", &window);

    srand(time(0));

    while (i <= n) {

        printf("\nSending frames: ");

        int end = i + window - 1;
        if (end > n) end = n;

        for (int j = i; j <= end; j++) {
            printf("%d ", j);
        }
        printf("\n");

        // choose which frame fails
        int failFrame = rand() % (end - i + 1);

        if (failFrame == 0) {
            printf("All frames received successfully\n");
            i = end + 1;
        } else {
            int failed = i + failFrame - 1;
            printf("Frame %d failed!\n", failed);
            printf("Go back and resend from Frame %d\n", failed);

            i = failed;  // go back
        }
    }

    printf("\nAll frames sent successfully!\n");

    return 0;
}
