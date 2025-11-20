#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipefd[2]; 
    pid_t pid1, pid2;


    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        exit(1);
    }

   
    if ((pid1 = fork()) == -1) {
        perror("fork failed");
        exit(1);
    }

    if (pid1 == 0) {  
        close(pipefd[0]);

        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execlp("ls", "ls", "-l", (char *)NULL);
        perror("execlp failed");  
        exit(1);
    }

    if ((pid2 = fork()) == -1) {
        perror("fork failed");
        exit(1);
    }

    if (pid2 == 0) { 
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);

   
        execlp("wc", "wc", "-l", (char *)NULL);
        perror("execlp failed");  
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
    int fd[2];
    pid_t pid1, pid2;

    if (pipe(fd) == -1)
    {
        perror("pipe failed");
        exit(1);
    }

    pid1 = fork();

    if (pid1 < 0)
    {
        perror("fork failed");
        exit(1);
    }

    if (pid1 == 0)
    {
     
        close(fd[0]);            
        dup2(fd[1], STDOUT_FILENO); 
        close(fd[1]);

        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls failed");
        exit(1);
    }
    pid2 = fork();

    if (pid2 < 0)
    {
        perror("fork failed");
        exit(1);
    }

    if (pid2 == 0)
    {
        
        close(fd[1]);           
        dup2(fd[0], STDIN_FILENO); 
        close(fd[0]);

        execlp("wc", "wc", "-l", NULL);
        perror("execlp wc failed");
        exit(1);
    }
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    return 0;
}
        exit(1);
    }
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return 0;
}
