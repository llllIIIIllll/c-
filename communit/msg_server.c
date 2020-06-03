#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include<unistd.h>

#define MSG_FILE "/etc/passwd"

struct msg_form
{
    long mtype;
    char mtext[256];
};

int main()
{
    int msqid;
    key_t key;
    struct msg_form msg;
    
    if ((key = ftok(MSG_FILE, 'z')) < 0)
    {
        perror("ftok error");
        exit(1);
    }
    
    printf("Message queue - server key is: %d\n", key);
    
    if ((msqid = msgget(key, IPC_CREAT|0777)) == -1)
    {
        perror("message error");
        exit(1);
    }
    
    printf("My msqid is: %d.\n", msqid);
    printf("My pid is: %d.\n", getpid());

    for(;;)
    {
        msgrcv(msqid, &msg, 256, 888, 0);
        printf("Server: receive msg.mtext is: %s.\n", msg.mtext);
        printf("Server: receive msg.mtype is: %d.\n", msg.mtype);
        
        msg.mtype = 999;
        sprintf(msg.mtext, "hello, I'm server: %d\n", getpid());
        msgsnd(msqid, &msg, sizeof(msg.mtext), 0);
    }
    
    return 0;
}