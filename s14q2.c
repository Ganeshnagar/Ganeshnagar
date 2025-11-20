#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
int main()
{
	struct stat st;
	char fname[20];
	int flag;
	printf("Enter the file name to be checked \n");
	scanf("%s", &fname);
	flag = stat(fname, &st);
	if (flag == 0)
	{
		printf("\n File exits \n");
		printf("\n Inode = %ld ", st.st_ino);
		printf("\n File size = %ld", st.st_size);
		printf("\n No of link = %ld", st.st_nlink);
		printf("\n Last Access time = %s", ctime(&st.st_atime));
		printf("\n Last modification time = %s", ctime(&st.st_mtime));

		printf("\n Permissions for files\n");
		if (st.st_mode && W_OK)
			printf("\t Write");
		if (st.st_mode && R_OK)
			printf("\t Read");
		if (st.st_mode && X_OK)
			printf("\t Execute");
	}
	else
	{
		printf("File does not exits.");
	}
}
