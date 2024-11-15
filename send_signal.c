/**
 * File: send_signal.c
 * Modified by: Jacob Tyree
 * 
 * Brief summary of program: Sends a signal to another program for it to receive the SIGUSR1 signal.
 * To send a signal, run the program that receives the signal, and then in another terminal, enter
 * ps aux and find the PID for the program that is running. Then run this program with the command
 * ./programname <PID>. 
 */



#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target PID>\n", argv[0]);
        exit(EXIT_FAILURE);
    }


    pid_t pid = atoi(argv[1]);
    srand(time(NULL));
    
    int random_value = rand() % 100;

    union sigval value; 
    value.sival_int = random_value;

    if(sigqueue(pid, SIGUSR1, value) == -1) {
        perror("sigerror");
        exit(EXIT_FAILURE);
    }
    printf("Sent SIGUSR1 with random integer %d to process %d\n", random_value, pid);
    
    return 0;
}