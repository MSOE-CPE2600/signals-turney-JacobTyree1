/**
 * Section: 121
 * File: sending.c
 * Modified by: Jacob Tyree
 * 
 * Brief Summary of program: Sends a signal to another program via their PID.
 * After a certain amount of time, it receives the signal back, which then the program sends 
 * the signal back to the other program. It prints what action it is doing to the console, 
 * and the game ends after 10 exchanges. 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

#define MAX_EXCHANGES 10

pid_t other_player_pid = 0;
int exchange_count = 0; //Keeping track of exchanges

void handle_ball(int signum, siginfo_t *info, void *context);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <other_player_PID>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    other_player_pid = atoi(argv[1]);
    srand(time(NULL));

    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;  
    sa.sa_sigaction = handle_ball;  
    sigemptyset(&sa.sa_mask); 

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    printf("Serving the ball to PID %d\n", other_player_pid);
    if (kill(other_player_pid, SIGUSR1) == -1) {
        perror("Failed to serve the ball");
        exit(EXIT_FAILURE);
    }

    while(1) {
        pause();
    }
    return 0;
}

void handle_ball(int signum, siginfo_t *info, void *context) {
    other_player_pid = info->si_pid;

    exchange_count++;
    if(exchange_count > MAX_EXCHANGES) {
        printf("Game Over. Exiting after %d exchanges.\n", MAX_EXCHANGES); //Exiting game when 10 exchanges are met

        if(kill(other_player_pid, SIGTERM) == -1) {
            perror("Faild to terminate the other player");
        }

        exit(0);
    }

    printf("Received the ball from PID %d. Exchange count: %d \a\n", other_player_pid, exchange_count);
    fflush(stdout);

    int wait_time = 1 + rand() % 2;
    sleep(wait_time);

    if (other_player_pid > 0) {
        printf("Sending the ball back to PID %d\n", other_player_pid);
        fflush(stdout);

        if (kill(other_player_pid, SIGUSR1) == -1) {
            perror("Failed to send the ball back");
            exit(EXIT_FAILURE);
        }
    }
}