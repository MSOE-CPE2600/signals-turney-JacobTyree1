/**
 * @file signal_segfault.c
 * @brief Program that dereferences a null pointer causing a segmentation fault
 */

/**
 * Modified by:
 * 
 * Brief summary of modifications:
 */


#include <stdio.h>
#include <signal.h>

void handle_segv(int signum);

int main (int argc, char* argv[]) {
    struct sigaction sa;
    sa.sa_handler = handle_segv;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGSEGV, &sa, NULL);

    // Declare a null pointer
    int* i = NULL;

    // Dereference the null pointer
    printf("The value of i is: %d\n", *i);

    // Return to exit the program
    return 0;
}

void handle_segv(int signum) {
    printf("Received signal: SIGSEGV (%d) - Segmentation fault detected\n", signum);
    return;
}