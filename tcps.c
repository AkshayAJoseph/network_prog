#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // 1. Create the socket (The Phone)
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // 2. Define the address and port (The Phone Number)
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Listen on any available network interface
    address.sin_port = htons(8080);

    // 3. Bind the socket to the port
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    // 4. Start listening for incoming calls (Queue size of 3)
    listen(server_fd, 3);
    printf("Server is waiting for a connection...\n");

    // 5. Accept the call (This "blocks" until a client connects)
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    printf("Connection established!\n");

    // 6. Communication
    read(new_socket, buffer, 1024);
    printf("Client says: %s\n", buffer);
    
    char *reply = "Hello from Server!";
    send(new_socket, reply, strlen(reply), 0);

    close(new_socket);
    close(server_fd);
    return 0;
}
