#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <sys/epoll.h>
#include <sys/errno.h>
#include <netdb.h>
#include <arpa/inet.h>


#define MAX_EVENTS 10
#define MAX_BUFFER_SIZE 1024
#define LISTEN_PORT 8000

struct global_data
{
    int server_sock;
    int server_epoll;
};

struct client_data
{
    char *read_buf;
    char *write_buf;
    int read_len;
    int read_off;
    int write_len;
    int write_off;
    int fd;
    struct sockaddr_in addr;
};

struct global_data g_gd;

struct client_data *alloc_client_data(int fd, struct sockaddr_in *addr = NULL)
{
    struct client_data *cd = NULL;
    cd = (struct client_data*)malloc(sizeof(struct client_data));
    if (cd == NULL)
    {
        return NULL;
    }
    cd->fd = fd;
    cd->read_len = MAX_BUFFER_SIZE;
    cd->read_off = 0;
    cd->write_len = MAX_BUFFER_SIZE;
    cd->write_off = 0;
    cd->read_buf = (char*)malloc(cd->read_len + 1);
    cd->write_buf = (char*)malloc(cd->write_len + 1);
    assert(cd->write_buf);
	assert(cd->read_buf);
	if(addr) memcpy(&cd->addr, addr, sizeof(&addr));
	return cd;
}

void free_client_data(struct client_data* cd)
{
    if (cd == NULL) return;
    close(cd->fd);
    if(cd->write_buf) free(cd->write_buf);
    if(cd->read_buf) free(cd->read_buf);
    free(cd);
    return;
}

int set_socket_non_block(int fd)
{
    int flags, result;
    flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1)
    {
        return -1;
    }
    flags |= O_NONBLOCK;
    result = fcntl(fd, F_SETFL, flags);
    if (result == -1)
    {
        return -1;
    }
    return 0;
}

int accept_client()
{
    int ret = -1;
    int addrlen;
    int client_sock;
    struct sockaddr_in remote_addr;
    struct epoll_event e_event;
    
    do
    {
        while(1)
        {
            addrlen = sizeof(struct sockaddr_in);            
            client_sock = accept(g_gd.server_sock, (struct sockaddr*)&remote_addr, (socklen_t*)&addrlen);
            if (client_sock == -1)
            {
                if(errno == EAGAIN || errno == EWOULDBLOCK)
                {
                    break;
                }
                else 
                {
                    printf("accept failed, error: %s\n", strerror(errno));
                    break;
                }
            }
            else
            {
                set_socket_non_block(client_sock);
                struct client_data *cd = alloc_client_data(client_sock, &remote_addr);
                assert(cd);
                e_event.events = EPOLLIN | EPOLLET;
                e_event.data.ptr = cd;
                if(epoll_ctl(g_gd.server_sock, EPOLL_CTL_ADD, client_sock, &e_event) == -1)
                {
                    printf("epoll_ctl client failed\n");
                    free_client_data(cd);
                }
                else
                {
                    printf("accept client: %s:%d\n",inet_ntoa(remote_addr.sin_addr), ntohs(remote_addr.sin_port));
                }
            }
        }
        ret = 0;
    }while (0);

    return ret;
}

int recv_data(struct client_data* cd)
{
    int ret = -1;
    int len_recv = 0;
    struct epoll_event e_event;
    
    if (cd == NULL) return ret;
    do
    {
        while(1)
        {
            len_recv = recv(cd->fd, cd->read_buf, cd->read_len, 0);
            if (len_recv == -1)
            {
                if (errno == EAGAIN)
                {
                    break;
                }
                else
                {
                    free_client_data(cd);
                    break;
                }
            }
            else if (len_recv == 0)
            {
                printf("client closed connection!\n");
                free_client_data(cd);
                break;
            }
            else
            {
				cd->read_buf[len_recv] = '\0';
				printf("[%s:%d] recv data: %s:%d \n", 
						inet_ntoa(cd->addr.sin_addr), 
						ntohs(cd->addr.sin_port),
						cd->read_buf,
						len_recv);
 
				cd->read_off = len_recv;
				
                // send response
                strcpy(cd->write_buf, "OK!");
                cd->write_off = strlen(cd->write_buf);

                e_event.events = EPOLLIN | EPOLLET;
                e_event.data.ptr = cd;
                epoll_ctl(g_gd.server_sock, EPOLL_CTL_ADD, cd->fd, &e_event);
            }
        }
        ret = 0;
    }while (0);

    return ret;
}

int send_data(client_data *cd)
{

	int ret = -1;
	int len_send = 0;
	struct epoll_event e_event;
 
	if(cd == NULL) return -1;
 
	do
	{
		len_send = send(cd->fd, cd->write_buf, cd->write_off, 0);
		if(len_send == -1)
		{
			if(errno != EAGAIN)
			{
				printf("send error %s \n", strerror(errno));
				free_client_data(cd);
			}
		}
		else if(len_send == 0)
		{
			free_client_data(cd);
		}
		else
		{
			e_event.events = EPOLLOUT | EPOLLET;
			e_event.data.ptr = cd;
			epoll_ctl(g_gd.server_epoll, EPOLL_CTL_MOD, cd->fd, &e_event);
		}
 
		ret = 0;
 
	}while(0);
 
	return ret;
}

void epoll_server()
{
    int signal_count = 0;
    struct sockaddr_in local_addr;
    struct epoll_event e_event;
	struct epoll_event e_events[MAX_EVENTS];

    
    memset(&g_gd, '\0', sizeof(struct global_data));

    do
    {
        g_gd.server_epoll = socket(AF_INET, SOCK_STREAM, 0);
        if (g_gd.server_sock < 0)
        {
            printf("create socket failed\n");
            break;
        }

        local_addr.sin_family = AF_UNSPEC;
        local_addr.sin_addr.s_addr = INADDR_NONE;
        local_addr.sin_port = htons(LISTEN_PORT);
        if(bind(g_gd.server_sock, (struct sockaddr*)&local_addr.sin_addr, (socklen_t)sizeof(local_addr) == -1))
        {
            printf("bind socket failed\n");
            break;
        }
        
        if (set_socket_non_block(g_gd.server_sock) < 0)
        {
            printf("set_socket_non_block failed\n");
            break;
        }

        if(listen(g_gd.server_sock, SOMAXCONN) < 0)
        {
            printf("listen failed\n");
            break;           
        }
        
        // create epoll handle
        g_gd.server_epoll = epoll_create(MAX_EVENTS);
        if (g_gd.server_epoll < 0)
        {
            printf("create epoll failed\n");
            break;           
        }

        e_event.events = EPOLLIN | EPOLLET;
        e_event.data.fd = g_gd.server_sock;
        if (epoll_ctl(g_gd.server_epoll, EPOLL_CTL_ADD, g_gd.server_sock, &e_event) < 0)
        {
            printf("control epoll failed\n");
            break;           
        }

        while (1)
        {
            printf("epoll wait... \n");
            signal_count = epoll_wait(g_gd.server_epoll, e_events, MAX_EVENTS, -1);
            if (signal_count == -1)
            {
                printf("epoll wait failed\n");
                break;           
            }
            printf("wait signals: %d \n", signal_count);
            for (int i = 0; i < signal_count; i++)
            {
                if (e_events[i].events & EPOLLERR || e_events[i].events & EPOLLHUP)
                {
                    printf("socket error\n");
                    continue;
                }
                else if (e_events[i].data.fd == g_gd.server_sock)
                {
                    accept_client();
                }
                else if (e_events[i].events & EPOLLIN)
                {
                    recv_data((struct client_data*)e_events[i].data.ptr);
                }
                else if (e_events[i].events & EPOLLOUT)
                {
                    send_data((struct client_data*)e_events[i].data.ptr);
                }
                else
                {
                    printf("epoll error\n");
                }
            }
        }

    } while (0);
    
    close(g_gd.server_sock);
    close(g_gd.server_epoll);

    return ;
}