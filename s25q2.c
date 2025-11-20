#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
   
    int file_desc = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file_desc == -1) {
        perror("Error opening file");
        return 1;
    }

    if (dup2(file_desc, STDOUT_FILENO) == -1) {
        perror("Error redirecting output");
        close(file_desc);
        return 1;
    }

   
    printf("This output will be written to the file output.txt\n");

    close(file_desc);

    return 0;
}
