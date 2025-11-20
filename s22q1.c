#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd;

 
    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd < 0)
    {
        perror("open failed");
        return 1;
    }

 
    dup2(fd, STDOUT_FILENO);

    
    printf("This is redirected output.\n");
    printf("Hello, this text will be saved in output.txt\n");

    close(fd);
    return 0;
}
