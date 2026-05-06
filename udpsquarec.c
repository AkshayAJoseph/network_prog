#include <stdio.h>
#include <arpa/inet.h>

int main() {
    int sd, num, result;
    struct sockaddr_in server_addr;
    socklen_t len = sizeof(server_addr);

    // 1. Setup
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter number to square: ");
    scanf("%d", &num);

    // 2. Send and Receive
    sendto(sd, &num, sizeof(num), 0, (struct sockaddr *)&server_addr, len);
    
    recvfrom(sd, &result, sizeof(result), 0, (struct sockaddr *)&server_addr, &len);
    
    printf("Square is: %d\n", result);

    return 0;
}
