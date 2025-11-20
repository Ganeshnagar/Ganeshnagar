#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
pid_t child_pid;
void child_death_handler(int sig)
{
    printf("\n[Parent] Child process terminated.\n");
}
void alarm_handler(int sig)
{
    printf("\n[Parent] Child did not finish in time. Killing child...\n");
    kill(child_pid, SIGKILL);   // kill child
}
int main()
{
    signal(SIGCHLD, child_death_handler);
    signal(SIGALRM, alarm_handler);
    child_pid = fork();
    if (child_pid < 0)
    {
        perror("fork failed");
        exit(1);
    }
    if (child_pid == 0)
    {
        execlp("ls", "ls", "-l", NULL);
        perror("execlp failed");
        exit(1);
    }
    else
    {
        printf("[Parent] Child created with PID: %d\n", child_pid);
        alarm(5);  
        wait(NULL);
        printf("[Parent] Exiting...\n");
    }
    return 0;
}
