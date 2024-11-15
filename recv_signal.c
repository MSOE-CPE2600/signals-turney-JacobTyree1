/**
 * Section: 121
 * File: recv_signal.c
 * Modified by: Jacob Tyree
 * 
 * Brief summary of program: Receives a signal from another program via the PID. 
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

    while (1) {
        pause();
    }
    return 0;
 }

 void handle_sigusr1(int signum, siginfo_t *info, void *context) {
    printf("Received SIGUSR1 with sival_int: %d\n", info->si_value.sival_int);
 }
