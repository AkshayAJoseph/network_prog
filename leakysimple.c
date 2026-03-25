#include <stdio.h>

int main() {
    int incoming, outgoing, bucket_size, n, store = 0;

    printf("Enter bucket size: ");
    scanf("%d", &bucket_size);
    printf("Enter outgoing rate: ");
    scanf("%d", &outgoing);
    printf("Enter number of inputs (time steps): ");
    scanf("%d", &n);

    while (n > 0) {
        printf("\n--- Time Step %d ---\n", n);
        printf("Enter incoming packet size: ");
        scanf("%d", &incoming);

        // 1. Check for Overflow
        if (incoming <= (bucket_size - store)) {
            store += incoming;
            printf("Bucket buffer: %d out of %d\n", store, bucket_size);
        } else {
            int dropped = (incoming + store) - bucket_size;
            printf("Dropped %d packets\n", dropped);
            store = bucket_size; // Bucket is now full
        }

        // 2. The "Leak" (Constant Outflow)
        if (store >= outgoing) {
            store -= outgoing;
        } else {
            store = 0; // Bucket emptied
        }
        
        printf("After outgoing, %d left in bucket\n", store);
        n--;
    }

    return 0;
}
