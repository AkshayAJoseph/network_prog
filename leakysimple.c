#include <stdio.h>

int main() {
    int incoming, outgoing, bucket_size, n, store = 0;

    printf("Enter bucket size, outgoing rate, and no. of inputs: ");
    scanf("%d %d %d", &bucket_size, &outgoing, &n);

    while (n--) {
        printf("\nEnter incoming packet size: ");
        scanf("%d", &incoming);

        if (incoming <= (bucket_size - store)) {
            store += incoming;
            printf("Bucket buffer size %d out of %d\n", store, bucket_size);
        } else {
            printf("Dropped %d packets (Bucket full!)\n", incoming);
        }

        // The "Leak" happens here
        store = (store >= outgoing) ? (store - outgoing) : 0;
        printf("After outgoing, %d left in bucket\n", store);
    }
    return 0;
}
