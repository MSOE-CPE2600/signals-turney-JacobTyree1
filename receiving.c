/**
 * Section: 121
 * File: receiving.c
 * Modified by: Jacob Tyree
 * 
 * Brief Summary of program: Waits to receive a signal from the sending program. 
 * Once it receives the signal, it sends the signal back to the sender. 
 * Each time it receives or sends, it prints that action to the console. The game 
 * ends after 10 exchanges. 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

pid_t sender_pid = 0;

void handle_ball(int signum, siginfo_t *info, void *context);
void handle_term(int signum);

int main() {
    srand(time(NULL));
    struct sigaction sa_term;
    sa_term.sa_handler = handle_term;
    sigemptyset(&sa_term.sa_mask);
    if (sigaction(SIGTERM, &sa_term, NULL) == -1) {
        perror("sigaction for SIGTERM");
        exit(EXIT_FAILURE);
    }



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
    sender_pid = info->si_pid; //getting pid from other program

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

void handle_term(int signum) {
    printf("Received SIGTERM. Exiting the game cleanly.\n"); //Exiting the game when 10 exchanges are met
    exit(0);
}
