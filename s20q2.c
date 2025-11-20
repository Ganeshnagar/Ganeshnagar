#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

void print_file_type(const char *filename) {
    struct stat file_stat;
    if (stat(filename, &file_stat) == -1) {
        perror("Error accessing file");
        return;
    }


    printf("File: %s\n", filename);

    if (S_ISREG(file_stat.st_mode)) {
        printf("Type: Regular file\n");
    } else if (S_ISDIR(file_stat.st_mode)) {
        printf("Type: Directory\n");
    } else if (S_ISCHR(file_stat.st_mode)) {
        printf("Type: Character device\n");
    } else if (S_ISBLK(file_stat.st_mode)) {
        printf("Type: Block device\n");
    } else if (S_ISFIFO(file_stat.st_mode)) {
        printf("Type: FIFO (named pipe)\n");
    } else if (S_ISLNK(file_stat.st_mode)) {
        printf("Type: Symbolic link\n");
    } else if (S_ISSOCK(file_stat.st_mode)) {
        printf("Type: Socket\n");
    } else {
        printf("Type: Unknown\n");
    }

    printf("\n");
}

int main(int argc, char *argv[]) {
  
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    for (int i = 1; i < argc; i++) {
        print_file_type(argv[i]);
    }

    return 0;
}
