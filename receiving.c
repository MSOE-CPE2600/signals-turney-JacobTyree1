/**
 * File: 
 * Modified by: 
 * 
 * Brief Summary of program: 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

pid_t sender_pid = 0;

void handle_ball(int signum, siginfo_t *info, void *context);

int main() {
    srand(time(NULL));

    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_ball;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    printf("Waiting to receive the ball... My PID is %d\n", getpid());
    while(1) {
        pause();
    }
    return 0;
}

void handle_ball(int signum, siginfo_t *info, void *context) {
    sender_pid = info->si_pid;

    printf("Received the ball from PID %d \a\n", sender_pid);
    fflush(stdout);

    int wait_time = 1 + rand() % 2;
    sleep(wait_time);

    if (sender_pid > 0) {
        printf("Sending the ball back to PID %d\n", sender_pid);
        fflush(stdout);

        if (kill(sender_pid, SIGUSR1) == -1) {
            perror("Failed to send the ball back");
            exit(EXIT_FAILURE);
        }
    }
}
