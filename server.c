#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h> 
#define PORT 8080 

int main()
{
    printf("Hello World!\n");
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    printf("%d\n", server_fd);
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);
    int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    int valread = read(new_socket, buffer, 1024);
    printf("%s\n", buffer);
    send(new_socket, hello, strlen(hello), 0);
    printf("Hello message sent\n");
    return 0;
}
