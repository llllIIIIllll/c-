#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<time.h>
#include<unistd.h>

int main()
{
    int fd;
    int n, i;
    char buff[1024];
    time_t tp;

    printf("I am %d process.\n", getpid());
    
    if((fd = open("fifo1", O_WRONLY)) < 0)
    {
        perror("Open fifo error");
        exit(1);
    }
    
    for(int i = 0; i < 10; i++)
    {
        time(&tp);
        n = sprintf(buff, "Process %d's time is %s", getpid(), ctime(&tp));
        printf("Send message: %s", buff);
        if(write(fd, buff, n+1) < 0)
        {
            perror("write error");
            close(fd);
            exit(1);
        }
        sleep(1);
    }
    
    close(fd);
    return 0;
}
