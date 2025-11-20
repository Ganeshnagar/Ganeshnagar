#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
 
        int i = 1;
        while (1) {
            printf("Child running... %d\n", i++);
            sleep(1);
        }
    }
    else {
      
        printf("Parent: Child PID = %d\n", pid);

        sleep(5);
        printf("Parent: Sending SIGSTOP (Suspend) to child.\n");
        kill(pid, SIGSTOP);

        sleep(5);
        printf("Parent: Sending SIGCONT (Resume) to child.\n");
        kill(pid, SIGCONT);

        sleep(5);
        printf("Parent: Sending SIGKILL to terminate child.\n");
        kill(pid, SIGKILL);
    }

    return 0;
}
