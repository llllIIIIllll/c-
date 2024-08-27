#define _XOPEN_SOURCE 700
#include <assert.h>
#include <signal.h>
#include <stdbool.h> /* false */
#include <stdio.h> /* perror */
#include <stdlib.h> /* EXIT_SUCCESS, EXIT_FAILURE */
#include <sys/wait.h> /* wait, sleep */
#include <unistd.h> /* fork, write */

#include <time.h>

static void
unblock_signal (int sig)
{
  sigset_t unblock_set;
  sigemptyset (&unblock_set);
  sigaddset (&unblock_set, sig);
  if (sigprocmask (SIG_UNBLOCK, &unblock_set, NULL) != 0)
	  ;
}


void signal_handler(int sig) {
    char s1[] = "SIGUSR1\n";
    char s2[] = "SIGUSR2\n";
    if (sig == SIGUSR1) {
        write(STDOUT_FILENO, s1, sizeof(s1));
    } else if (sig == SIGUSR2) {
        write(STDOUT_FILENO, s2, sizeof(s2));
    }
    signal(sig, signal_handler);
}

pid_t run() {
    pid_t pid;
    sigset_t block_set;

    pid = fork();
    if (pid == -1) {
        perror("fork");
        assert(false);
    } else {
        if (pid == 0) {
            while (1);
            exit(EXIT_SUCCESS);
        }
        sigaddset (&block_set, SIGCHLD);
        kill(pid, SIGUSR1);
        sleep(1);
        kill(pid, SIGUSR2);
        sleep(1);
        unblock_signal (SIGCHLD);
    }
    return pid;
}


int main() {


    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);

    while (1) {
        pid_t p=run();
        kill(p, 1);

    }
    return EXIT_SUCCESS;

}
