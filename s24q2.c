#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
pid_t child_pid;
void child_death_handler(int sig){
    printf("Child process terminated.\n");
}
void alarm_handler(int sig){
    printf("Child did not finished in 5 sec ,kill child..\n");
    kill(child_pid,SIGKILL);
}
int main()
{
    signal(SIGCHLD,child_death_handler);
    signal(SIGALRM,alarm_handler);
    child_pid =fork();
    if(child_pid <0)
    {
        perror("fork");
        exit(1);
    }
    if(child_pid ==0){
        execlp("sleep" ,"sleep","10", NULL);
        perror("execlp");
        exit(1);
    }
    alarm(5);
    wait(NULL);
    printf("Parent exiting.\n");
    return 0;
}