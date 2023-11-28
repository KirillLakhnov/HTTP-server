#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

const size_t MAX_LEN_REQUEST_BUF = 1024;

int main ()
{
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0)
    {
        perror("Error creater client socket");
        exit(1);
    }

    struct sockaddr_in client_socket_addr = {};
    bzero(&client_socket_addr, sizeof(client_socket_addr));

    client_socket_addr.sin_family = AF_INET;
    client_socket_addr.sin_port = htons(80);
    client_socket_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (connect(client_socket, (struct sockaddr*)&client_socket_addr, sizeof(client_socket_addr)) < 0)
    {
        perror("Error connect client socket");
        exit(1);
    }

    char request[MAX_LEN_REQUEST_BUF] = "";
    printf("Message:\n");
    
    size_t index = 0;
    do
    {
        fgets(request + index, MAX_LEN_REQUEST_BUF - index, stdin);

        index = strlen(request); 
        *(request + index) = ' ';
        index++;
    } while (!(feof(stdin) != 0) && (index < MAX_LEN_REQUEST_BUF)); // Конец ввода задается Ctrl+D;
    
    if (send(client_socket, request, sizeof(request), 0) < 0)
    {
        perror("Error write client socket");
        exit(1);
    }

    /*char answer[100] = "";

    if (recv(client_socket, answer, sizeof(answer), 0) < 0)
    {
        perror("Error read client socket");
        exit(1);
    }

    printf("Answer: %s", answer);*/

    shutdown(client_socket, SHUT_RDWR);
    close (client_socket);

    return 0;
}