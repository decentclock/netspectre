#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#define PORT 8080

int main()
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    int val = connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    if (val == -1)
        printf("ERROR CODE: %i\n", errno);

    char hello[2] = {'\x01','\x00'};
    int characters_sent = send(sock, &hello, 2, 0);

    printf("I just sent %i characters\n", characters_sent);

    char buffer[1] = {0};
    valread = read(sock, buffer, 1);
    printf("%i\n", buffer[0]);

    shutdown(sock, 2);
    return 0;
}
