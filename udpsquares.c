#include <stdio.h>
#include <arpa/inet.h>

int main() {
    int sd, num, square;
    struct sockaddr_in server_addr, client_addr;
    socklen_t len = sizeof(client_addr);

    // 1. Setup
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bind(sd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    printf("Server waiting for a number...\n");

    // 2. Receive, Math, Send
    recvfrom(sd, &num, sizeof(num), 0, (struct sockaddr *)&client_addr, &len);
    
    square = num * num;
    
    sendto(sd, &square, sizeof(square), 0, (struct sockaddr *)&client_addr, len);

    return 0;
}
