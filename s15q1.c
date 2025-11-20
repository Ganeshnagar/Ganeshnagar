#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
int main() {
    DIR *d;
    struct dirent *de;
    struct stat st;
    char name[256];
    long n;
    printf("Enter size in bytes: ");
    scanf("%ld", &n);
    d = opendir(".");
    if (d == NULL) {
        printf("Unable to open directory.\n");
        return 1;
    }
    while ((de = readdir(d)) != NULL) {
        stat(de->d_name, &st);
        if (S_ISREG(st.st_mode) && st.st_size > n) {
            printf("%s  (%ld bytes)\n", de->d_name, st.st_size);
        }
    }
    closedir(d);
    return 0;
}
