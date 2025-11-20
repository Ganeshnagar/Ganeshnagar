#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    int fd[2];
    pid_t c1, c2;


    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    c1 = fork();
    if (c1 == 0) {
        close(fd[0]);           
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        execlp("ls", "ls", "-l", NULL);
        perror("exec command1");
        exit(1);
    }

    c2 = fork();
    if (c2 == 0) {
        close(fd[1]);             
        dup2(fd[0], STDIN_FILENO);  
        close(fd[0]);

        execlp("wc", "wc", "-l", NULL);
        perror("exec command2");
        exit(1);
    }

    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);

    return 0;
}
