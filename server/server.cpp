#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <vector>

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>

/* #ifdef __APPLE__
    #include <sys/poll.h>
#else
    #include <sys/epoll.h>
#endif */
#include <sys/poll.h>

#include "include/http.hpp"

const size_t POLL_SIZE = 1024;

int set_nonblock (int socket_fd)
{
    if (fcntl(socket_fd, F_SETFL, fcntl(socket_fd, F_GETFL, 0) | O_NONBLOCK) == -1) 
    {
		return -1;
	}
	return 0;
}

int main ()
{
    int master_socket = socket(AF_INET, SOCK_STREAM, 0); //TCP-сокет для приема запросов на соединение.
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

    if (set_nonblock(master_socket) == -1)
    {
        perror("Error creating a non-blocking socket");
    }

    if (listen(master_socket, SOMAXCONN) < 0)
    {
        perror("Error listen master socket");
        exit(1);
    }

    struct pollfd active_set[POLL_SIZE] = {};
    active_set[0].fd = master_socket;
    active_set[0].events = POLLIN;
    active_set[0].revents = 0;
    int size_active_set = 1;

    //Цикл проверки состояния сокетов
    while (1)
    {
        int poll_ret = poll(active_set, size_active_set, -1);

        if (poll_ret < 0)
        {
            perror("Error poll");
            exit(1);
        }

        //TODO: оптимизация работы с памятью 
        for (int i = 0; i < size_active_set; i++)
        {
            if (active_set[i].revents & POLLIN)
            {
                active_set[i].revents &= ~POLLIN;

                if (i == 0)
                {
                    int slave_socket = accept(master_socket, 0, 0);
                    if (slave_socket < 0)
                    {
                        perror("Error creater slave socket");
                        exit(1);
                    }

                    if (size_active_set < POLL_SIZE)
                    {
                        active_set[size_active_set].fd = slave_socket;
                        active_set[size_active_set].events = POLLIN;
                        active_set[size_active_set].revents = 0;
                        size_active_set++;
                    }
                    else
                    {
                        printf ("size_active_set == POLL_SIZE: no connect.\n");

                        shutdown(slave_socket, SHUT_RDWR);
                        close(slave_socket);
                    }
                }
                else
                {
                    char request_buf[MAX_LEN_REQUEST_BUF] = "";
                    if (recv(active_set[i].fd, request_buf, sizeof(request_buf), 0) < 0)
                    {
                        perror("Error read slave socket");
                        exit(1);
                    }

                    printf("Request:\n%s\n", request_buf);

                    HTTP::request client_request(request_buf);
                    client_request.dump();
                    client_request.answer();

                    printf("Good work!\n");

                    active_set[i].events = POLLOUT;
                }
            }
        }
    }

    shutdown(master_socket, SHUT_RDWR);
    close(master_socket);

    return 0;
}