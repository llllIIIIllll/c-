//
//  server.c
//  udp
//
//  Created by lovekun on 14-11-2.
//  Copyright (c) 2014年 care.jiangnan. All rights reserved.
//
 
/* server.c */
 
#include <stdio.h> /* These are the usual header files */
#include <string.h>
#include <unistd.h> /* for close() */
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
 
#define PORT 1234 /* Port that will be opened */
#define MAXDATASIZE 100 /* Max number of bytes of data */
 
int main()
{
 
    
    int sockfd; /* socket descriptors */
    struct sockaddr_in server; /* server's address information */
    struct sockaddr_in client; /* client's address information */
    socklen_t sin_size;
    int num;
    char recvmsg[MAXDATASIZE]; /* buffer for message */
    char sendmsg[MAXDATASIZE];
    char condition[] = "quit";
    /* Creating UDP socket */
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        /* handle exception */
        perror("Creating socket failed.");
        exit(1);
    }
    
    bzero(&server,sizeof(server));
    server.sin_family=AF_INET;
    server.sin_port=htons(PORT);
    server.sin_addr.s_addr = htonl (INADDR_ANY);
    if (bind(sockfd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1) {
        /* handle exception */
        perror("Bind error.");
        exit(1);
    }
    
    sin_size=sizeof(struct sockaddr_in);
    static uint8_t last_seq = 0;
    static int total_count = 0;
    static int total_error_count = 0;
    while (1) {
        num = recvfrom(sockfd,recvmsg,MAXDATASIZE,0,(struct sockaddr *)&client,&sin_size);
        if (num < 0){
            perror("recvfrom error\n");
            exit(1);
        }
        
        recvmsg[num] = '\0';
        uint8_t num_seq = (int)recvmsg[0];
        total_count = num_seq;
        if (num_seq-last_seq)
            total_error_count++;
        
        last_seq = num_seq;
        if(strcmp(recvmsg,condition)==0) break;
        
        if (last_seq == 255)
        {
printf("(%3d) -- (%3d) -- result (%d / %d) from %s\n", last_seq, num_seq, total_error_count,total_count,inet_ntoa(client.sin_addr) ); /* prints client's IP */
            total_count = 0;
            total_error_count = 0;
        }        
        // int i=0;
        // for(i = 0 ; i < num ; i ++)
        // {
        //     sendmsg[i] = recvmsg[num-1-i];
        // }
        // sendmsg[num]='\0';
        
        // sendto(sockfd,sendmsg,strlen(sendmsg),0,(struct sockaddr *)&client,sin_size);
        
    }
    
    close(sockfd); /* close listenfd */ 
}