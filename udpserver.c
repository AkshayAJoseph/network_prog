#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

int main() {
	int sockfd;
    char buffer[1024];
    char *hello = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);
    int n;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    n = recvfrom(sockfd, buffer, 1024, 0,(struct sockaddr *)&cliaddr, &len);
    buffer[n] = '\0';
    printf("%s\n", buffer);

    sendto(sockfd, hello, strlen(hello), 0,(struct sockaddr *)&cliaddr, len);

    close(sockfd);
    return 0;
}

