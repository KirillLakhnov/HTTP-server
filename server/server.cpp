#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "include/http.hpp"

int main ()
{
    int master_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (master_socket < 0)
    {
        perror("Error creater master socket");
        exit(1);
    }

    struct sockaddr_in master_socket_addr = {};
    bzero(&master_socket_addr, sizeof(master_socket_addr));

    master_socket_addr.sin_family = AF_INET;
    master_socket_addr.sin_port = htons(80);
    master_socket_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(master_socket, (struct sockaddr*)&master_socket_addr, sizeof(master_socket_addr)) < 0)
    {
        perror("Error bind master socket");
        exit(1);
    }

    if (listen (master_socket, SOMAXCONN) < 0)
    {
        perror("Error listen master socket");
        exit(1);
    }

    

    while (1)
    {
        int slave_socket = accept (master_socket, 0, 0);
        if (master_socket < 0)
        {
            perror("Error creater slave socket");
            exit(1);
        }

        char request_buf[MAX_LEN_REQUEST_BUF] = "";
        if (recv(slave_socket, request_buf, sizeof(request_buf), 0) < 0)
        {
            perror("Error read slave socket");
            exit(1);
        }
        
        printf("Request:\n%s\n", request_buf);

        HTTP::request client_request(request_buf);
        client_request.dump();

        printf("Good work!\n");

        shutdown(slave_socket, SHUT_RDWR);
        close(slave_socket);
    }

    shutdown(master_socket, SHUT_RDWR);
    close(master_socket);

    return 0;
}