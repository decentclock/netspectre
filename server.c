#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h> 
#define PORT 8080 

int main()
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1] = {0};
    char flag = '\x00';

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);
    int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    int valread = read(new_socket, buffer, 1);
    printf("%i\n", buffer[0]);

    char bitstream[5] = {0,1,2,3,4};
    if (buffer[0] < 5)
    {
        if (bitstream[buffer[0]])
        {
            flag = '\x01';
            printf("Flag set to true\n");
        }
    }
    return 0;
}
