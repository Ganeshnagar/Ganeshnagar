#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(int argc ,char *argv[])
{
if(argc != 2){
printf("\n Invalid no of argument.");
}
char *filename = argv[1];
if(access(filename,F_OK))
{
printf("%s file present in directory.",filename);
}
else
{
printf("%s file is not in direcotry.",filename);
}
return 0;
}
