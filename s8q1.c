#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> 
#include <sys/types.h>
#include <sys/stat.h>
int main() {
   
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    if (fd == -1) {
        perror("Error opening file");
        exit(1);
    }

    
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("Error redirecting stdout");
        close(fd);
        exit(1);
    }

    
    close(fd);
    printf("This will be written to output.txt instead of the terminal.\n");
    printf("All subsequent printf calls will also go to the file.\n");

    return 0;
}
