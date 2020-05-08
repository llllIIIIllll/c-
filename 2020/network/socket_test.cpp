#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

int main()
{
    int sockfd, status;
    struct addrinfo hints, *res;
    
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    status = getaddrinfo(NULL, "3490", &hints, &res);
    if (status < 0)
    {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    }
    
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    
    // set reuse
    int yes = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) 
    {
        perror("setsocketopt");
        exit(-1);
    }
    
    bind(sockfd, res->ai_addr, res->ai_addrlen);

    for (; res != NULL; res=res->ai_next)
    {
        struct sockaddr_in *in = (struct sockaddr_in*)(res->ai_addr);
        char ipstr[INET6_ADDRSTRLEN];
        int port;

        inet_ntop(res->ai_family, &(in->sin_addr), ipstr, sizeof ipstr);
        port = ntohs(in->sin_port);
        printf("3490 ip: %s : %d\n", ipstr, port);    
        
        in = (struct sockaddr_in *)&(hints.ai_addr);
        inet_ntop(hints.ai_family, &(in->sin_addr), ipstr, sizeof ipstr);
        port = ntohs(in->sin_port);
        printf("3490 ip: %s : %d\n", ipstr, port);    
    }
    
    connect(sockfd, res->ai_addr, res->ai_addrlen);
}
