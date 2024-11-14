/**
 * File: signal_sigaction.c
 * Modified by: Jacob Tyree
 * 
 * Brief summary of program: Program waits in an infinte loop until the user terminates 
 * the program. In that loop, if a signal is sent, then it will print out the signal from the pid. 
 * One command that can be used to send SIGUSR1 to the process is: kill -USR1 <pid>
 * Where the pid can be found using ps aux in another terminal. 
 */


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigusr1(int signum, siginfo_t *info, void *context);

int main() {
    struct sigaction sa;

    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_sigusr1;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    while(1) {
        pause(); //This is waiting for signals
    }
    return 0;
}

void handle_sigusr1(int signum, siginfo_t *info, void *context) {
    printf("Received SIGUSR1 from process ID: %d\n", info->si_pid);
}
