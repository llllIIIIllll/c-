#include <stdio.h>
#include <unistd.h>

int main()
{
    int fd[2];
    pid_t pid;
    char buff[20];

    if(pipe(fd) < 0)
        printf("Create pipe error!");
    
    if((pid = fork()) < 0)
        printf("Fork error!");
    else if(pid > 0)
    {
        close(fd[0]);
        write(fd[1], "hello world\n", 12);
    }
    else
    {
        close(fd[1]);
        read(fd[0], buff, 20);
        printf("%s", buff);
    }
    return 0;
}