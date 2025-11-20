#include<stdio.h>
#include<dirent.h>
int main(){
    DIR *d;
    struct dirent *de;
    int count=0;
    d = opendir(".");
    if(d==NULL)
    {
        printf("\n Unable to oepn the directory");
        return 1;
    }
    printf("\n Filees in current director.");
    while((de=readdir(d))!=NULL)
    {
        printf("%s\n",de->d_name);
        count++;
    }
    closedir(d);
    printf("\n Total no of files :%d\n",count);
    return 0;
}