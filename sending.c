#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

#define MAX_EXCHANGES 10

pid_t other_player_pid = 0;
int exchange_count = 0;

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
        printf("Game Over. Exiting after %d exchanges.\n", MAX_EXCHANGES);
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