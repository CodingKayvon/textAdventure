#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <sys/wait.h>

using namespace std;

#define MAX_LINE 80 // The maximum length command

int parse_command(char command[], char *args[]) {
    int i = 0;
    char *pch = strtok(command, " \n");
    while (pch != NULL) {
        args[i] = pch;
        i++;
        pch = strtok(NULL, " \n");
    }
    args[i] = NULL; // Null-terminate the args array
    return i;
}

int main(int argc, char *argv[]) {
    char command[MAX_LINE];       // the command that was entered
    char last_command[MAX_LINE];  // the last command that was entered
    char *args[MAX_LINE / 2 + 1]; // hold parsed out command line arguments
    char *args_pipe[MAX_LINE / 2 + 1]; // hold arguments for the command after pipe
    int should_run = 1;           /* flag to determine when to exit program */

    while (should_run) {
        printf("What will you do? ");
        fgets(command, MAX_LINE, stdin);

        command[strcspn(command, "\n")] = 0; // Remove the trailing newline character

         // Check for exit command
        if (strcmp(command, "quit") == 0) {
            should_run = 0; // Exit the program
            continue;
        }
    }

    return 0;
}