#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd[2];   
    pid_t pid;

    if (pipe(fd) == -1)
    {
        perror("pipe failed");
        return 1;
    }

    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (pid == 0)     
    {
        close(fd[0]); 

        char *m1 = "Hello World\n";
        char *m2 = "Hello SPPU\n";
        char *m3 = "Linux is Funny\n";

        write(fd[1], m1, strlen(m1));
        write(fd[1], m2, strlen(m2));
        write(fd[1], m3, strlen(m3));

        close(fd[1]);  
    }
    else            
    {
        close(fd[1]);  

        char buffer[100];
        int n = read(fd[0], buffer, sizeof(buffer));

        buffer[n] = '\0';  
        printf("Messages from pipe:\n%s", buffer);

        close(fd[0]); 
    }

    return 0;
}
