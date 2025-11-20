#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void handle_sighup(int sig) {
    printf("Child received SIGHUP signal.\n");
}

void handle_sigint(int sig) {
    printf("Child received SIGINT signal.\n");
}

void handle_sigquit(int sig) {
    printf("Child received SIGQUIT signal. My Papa has Killed me!!!\n");
    exit(0);  
}

int main() {
    pid_t pid = fork();  

    if (pid < 0) {
       
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        
        signal(SIGHUP, handle_sighup);
        signal(SIGINT, handle_sigint);
        signal(SIGQUIT, handle_sigquit);

        
        while (1) {
            pause();  
        }
    } else {
      
        sleep(3); 

        for (int i = 0; i < 4; i++) {
            sleep(3);  
            if (i % 2 == 0) {
               
                kill(pid, SIGHUP);
            } else {
                
                kill(pid, SIGINT);
            }
        }

      
        sleep(3); 
        kill(pid, SIGQUIT);
        wait(NULL);
        printf("Parent process terminating.\n");
    }

    return 0;
}
