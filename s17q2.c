#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main()
{
    int fd[2];
    pid_t pid1, pid2;

    sigset_t block_set;
    sigemptyset(&block_set);
    sigaddset(&block_set, SIGINT);
    sigaddset(&block_set, SIGQUIT);

    if (sigprocmask(SIG_BLOCK, &block_set, NULL) < 0) {
        perror("sigprocmask");
        exit(1);
    }

    if (pipe(fd) == -1) {
        perror("pipe failed");
        exit(1);
    }

    pid1 = fork();
    if (pid1 == 0) {
        sigprocmask(SIG_UNBLOCK, &block_set, NULL);

        close(fd[0]);                    
        dup2(fd[1], STDOUT_FILENO);     
        close(fd[1]);

        execlp("ls", "ls", "-l", NULL);
        perror("exec ls");
        exit(1);
    }

    pid2 = fork();
    if (pid2 == 0) {
        sigprocmask(SIG_UNBLOCK, &block_set, NULL);

        close(fd[1]);                
        dup2(fd[0], STDIN_FILENO);   
        close(fd[0]);

        execlp("wc", "wc", "-l", NULL);
        perror("exec wc");
        exit(1);
    }

    close(fd[0]);
    close(fd[1]);

    wait(NULL);
    wait(NULL);
    sigprocmask(SIG_UNBLOCK, &block_set, NULL);

    return 0;
}
