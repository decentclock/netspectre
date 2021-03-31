#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h>
#include <immintrin.h>
#define PORT 8080 

int main()
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    char buffer[2] = {0};
    char flag = '\x00';

    /* Initialize the two argument vectors */
    __m256 evens = _mm256_set_ps(2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0);
    __m256 odds = _mm256_set_ps(1.0, 3.0, 5.0, 7.0, 9.0, 11.0, 13.0, 15.0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    while (1)
    {
        int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        int valread = read(new_socket, buffer, 2);

        if (buffer[0] == '\x00')
        {
            char bitstream[5] = {0,1,2,3,4};
            if (buffer[1] < 5)
            {
                if (bitstream[buffer[1]])
                {
                    flag = '\x01';
                    printf("Flag set to true\n");

                    /* Compute the difference between the two vectors */
                    __m256 result = _mm256_sub_ps(evens, odds);

                    /* Display the elements of the result vector */
                    float* f = (float*)&result;
                    printf("%f %f %f %f %f %f %f %f\n", f[0], f[1], f[2], f[3], f[4], f[5], f[6], f[7]);
                }
            }
        }
        else if (buffer[0] == '\x01')
        {
            send(new_socket, &flag, 1, 0);
        }
        else if (buffer[0] == '\xFF')
        {
            shutdown(new_socket, 2);
            break;
        }
        shutdown(new_socket, 2);
    }

    shutdown(server_fd, 2);
    return 0;
}


/* Please compile server.c on Windows OS with the following command:
 * gcc -mavx -o server server.c
 * */