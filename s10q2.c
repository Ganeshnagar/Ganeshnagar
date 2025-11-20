#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd[2];
    pid_t pid;
    char message[] = "Hello from Parent to Child!";
    char buffer[100];

  
    if (pipe(fd) == -1) {
        perror("pipe failed");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {  
       
        close(fd[1]);   

        int n = read(fd[0], buffer, sizeof(buffer));
        buffer[n] = '\0';
        printf("Child received: %s\n", buffer);

        close(fd[0]);
    }
    else {              
        
        close(fd[0]);     

        write(fd[1], message, strlen(message));
        printf("Parent sent: %s\n", message);

        close(fd[1]);
    }

    return 0;
}
