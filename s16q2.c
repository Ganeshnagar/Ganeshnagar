#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <time.h>

void handle_sighup(int sig) {
    printf("Child received SIGHUP signal\n");
}

void handle_sigint(int sig) {
    printf("Child received SIGINT signal\n");
}

void handle_sigquit(int sig) {
   
    printf("My DADDY has Killed me!!!\n");
    exit(0);
}

int main() {
    pid_t child_pid;

   
    child_pid = fork();

    if (child_pid == -1) {
    
        perror("Fork failed");
        return 1;
    }

    if (child_pid == 0) {
        
        signal(SIGHUP, handle_sighup);
        signal(SIGINT, handle_sigint);
        signal(SIGQUIT, handle_sigquit);

       
        printf("Child process is waiting for signals...\n");
        while (1) {
           
            sleep(1);
        }
    } else {
       
        for (int i = 0; i < 10; i++) {
            if (i % 2 == 0) {
              
                kill(child_pid, SIGHUP);
            } else {
                
                kill(child_pid, SIGINT);
            }
            sleep(3); 

       
        printf("Parent will send SIGQUIT to terminate the child...\n");
        sleep(30);  
        kill(child_pid, SIGQUIT);

        
        wait(NULL);
    }

    return 0;
}
