#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
void alarm_handler(int sig)
{
    printf("Alarm is fired! (SIGALRM received)\n");
}
int main()
{
    pid_t pid;
    signal(SIGALRM, alarm_handler);
    pid = fork();
    if (pid < 0)
    {
        perror("fork failed");
        exit(1);
    }
    if (pid == 0)  
    {
        sleep(3); 
        kill(getppid(), SIGALRM);
        printf("Child sent SIGALRM to parent.\n");
    }
    else  
    {
        printf("Parent waiting for signal from child...\n");
        pause(); 
        printf("Parent received signal. Exiting...\n");
    }
    return 0;
}
