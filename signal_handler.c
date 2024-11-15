/**
 * @file signal_handler.c
 * @brief Sets a signal handler for SIGINT, the handler prints a message and then quits
 */

/**
 * Section: 121
 * Modified by: Jacob Tyree
 * 
 * Brief summary of modifications:
 * Removed the exit command that would exit when it received a signal such as
 * Ctrl + C or SIGINT. The way to exit the program is by entering the command
 * "kill -SIGKILL <PID>". You can find the PID by entering ps aux. 
 */


#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Signal handler for SIGINT - prints a message and exits
 */
void handle_signal() {
    printf("Received a signal\n");
    
}

int main() {

    // Register for the signal
    signal(SIGINT, handle_signal);

    // Wait until a signal is received
    while(1) {
        printf("Sleeping\n");
        sleep(1);
    }

    return 0;
}