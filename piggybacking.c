#include <stdio.h>

int main() {
    int n, i;

    printf("Enter number of frames: ");
    scanf("%d", &n);

    for(i = 1; i <= n; i++) {

        printf("\nA sends Frame %d to B\n", i);

        // B sends data + ACK together
        printf("B sends Frame %d to A (with ACK for Frame %d)\n", i+1, i);
    }

    return 0;
}
