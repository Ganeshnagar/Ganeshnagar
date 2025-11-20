#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

void block_signals() {
    sigset_t new_set;
    sigemptyset(&new_set);
    sigaddset(&new_set, SIGINT);
    sigaddset(&new_set, SIGQUIT);
    sigprocmask(SIG_BLOCK, &new_set, NULL);
}

int main() {
    int pipe_fd[2];  
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return 1;
    }

    block_signals();

    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        return 1;
    }

    if (pid1 == 0) {
     
        close(pipe_fd[0]);  
        dup2(pipe_fd[1], STDOUT_FILENO);  
        close(pipe_fd[1]);  

        execlp("ls", "ls", "-l", NULL);
        perror("execlp(ls)");
        exit(1); 
    }

    pid_t pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        return 1;
    }

    if (pid2 == 0) {
        
        close(pipe_fd[1]);
        dup2(pipe_fd[0], STDIN_FILENO); 
        close(pipe_fd[0]); 

     
        execlp("wc", "wc", "-l", NULL);
        perror("execlp(wc)");
        exit(1);  
    }

    close(pipe_fd[0]);
    close(pipe_fd[1]);

    
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
