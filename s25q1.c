#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd;

    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd < 0) {
        perror("open");
        return 1;
    }

    close(STDOUT_FILENO);

    dup(fd);

  
    printf("This text is redirected into output.txt\n");
    printf("Redirection using open() and dup()\n");

    close(fd);
    return 0;
}
