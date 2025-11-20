#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
int main(int argc, char *argv[])
{
  int i;
  struct stat st;
  for (i = 1; i < argc; i++)
  {
    stat(argv[i], &st);
    printf("/n %s ",argv[i]);
    printf("inode= %ld", st.st_ino);

    if (S_ISDIR(st.st_mode))

      printf("\n type of file %s is directory", argv[i]);
    else if (S_ISREG(st.st_mode))
      printf("\n type of file %s is Regular file", argv[i]);
    else
      printf("\n other than  directory or regular file...");
  }
  return 0;
}