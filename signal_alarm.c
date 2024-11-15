/**
 * Section: 121
 * File: signal_alarm.c
 * Modified by: Jacob Tyree
 * 
 * Brief summary of program: Sets an alarm for 5 seconds. Once the 5 seconds have passed, 
 * it sends a SIGALRM signal to the handler which prints out the signal that was received. 
 */



#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void handle_alarm(int signum);

int main() {
    printf("Setting an alarm for 5 seconds...\n");
    struct sigaction sa;
    
    sa.sa_handler = handle_alarm;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGALRM, &sa, NULL);
    alarm(5);

    while(1) {
        pause(); //Waiting for the signals. 
    }
    return 0;
}

void handle_alarm(int signum) {
    printf("Received signal: SIGALRM (%d)\n", signum);
}