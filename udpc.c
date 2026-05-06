#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int sockfd;
    char buffer[1024];
    char *hello = "Hello from client";
    struct sockaddr_in servaddr;
    socklen_t len = sizeof(servaddr);
    int n;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

    sendto(sockfd, hello, strlen(hello), 0,(struct sockaddr *)&servaddr, len);

    n = recvfrom(sockfd, buffer, 1024, 0,(struct sockaddr *)&servaddr, &len);
    buffer[n] = '\0';
    printf("%s\n", buffer);

    close(sockfd);
    return 0;
}

