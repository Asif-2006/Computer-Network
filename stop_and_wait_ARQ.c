#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// function to simulate ACK (receiver side)
int receiveACK(int frame) {
    int ack = rand() % 2;   // 0 = lost, 1 = received

    if (ack == 1) {
        printf("Receiver: Frame %d received\n", frame);
        printf("Receiver: ACK sent for Frame %d\n", frame);
        return 1;
    } else {
        printf("Receiver: ACK lost for Frame %d\n", frame);
        return 0;
    }
}

int main() {
    int n, i;

    printf("Enter number of frames: ");
    scanf("%d", &n);

    srand(time(0));  // for random values

    for (i = 1; i <= n; i++) {

        printf("\nSender: Sending Frame %d...\n", i);

        if (receiveACK(i)) {
            printf("Sender: ACK received for Frame %d\n", i);
        } else {
            printf("Sender: Timeout! Resending Frame %d...\n", i);
            i--;   // resend same frame
        }
    }

    printf("\nAll frames sent successfully!\n");

    return 0;
}
