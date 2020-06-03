#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>

int main()
{
    int fd;
    int len;
    char buff[1024];

    if(mkfifo("fifo1", 0666) < 0 && errno != EEXIST)
        perror("Create fifo file");
        
    if((fd = open("fifo1", O_RDONLY)) < 0)
    {
        perror("open fifo error");
        exit(1);
    }
    
    while (len = read(fd, buff, 1024) > 0)
    {
        printf("message is: %s", buff);
    }
    
    close(fd);
    return 0;
}