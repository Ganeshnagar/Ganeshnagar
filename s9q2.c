#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

void identify_file_type(const char *path) {
    struct stat file_stat;

    if (stat(path, &file_stat) == -1) {
        perror("Error getting file status");
        return;
    }

    if (S_ISDIR(file_stat.st_mode)) {
        printf("The file %s is a Directory.\n", path);
    } else if (S_ISCHR(file_stat.st_mode)) {
        printf("The file %s is a Character Device.\n", path);
    } else if (S_ISBLK(file_stat.st_mode)) {
        printf("The file %s is a Block Device.\n", path);
    } else if (S_ISREG(file_stat.st_mode)) {
        printf("The file %s is a Regular File.\n", path);
    } else if (S_ISFIFO(file_stat.st_mode)) {
        printf("The file %s is a FIFO (Named Pipe).\n", path);
    } else if (S_ISLNK(file_stat.st_mode)) {
        printf("The file %s is a Symbolic Link.\n", path);
    } else if (S_ISSOCK(file_stat.st_mode)) {
        printf("The file %s is a Socket.\n", path);
    } else {
        printf("The file %s is of an unknown type.\n", path);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file-path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

   
    identify_file_type(argv[1]);

    return 0;
}
