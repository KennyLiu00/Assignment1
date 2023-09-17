
/**
 * Assignment 2: Simple UNIX Shell
 * @file pcbtable.h
 * @author Kenny Liu, Jesus Mendoza
 * @brief This is the main function of a simple UNIX Shell. You may add additional functions in this file for your implementation
 * @version 0.1
 */
// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

#define MAX_LINE 80 // The maximum length command

/**
 * @brief parse out the command and arguments from the input command separated by spaces
 *
 * @param command
 * @param args
 * @return int
 */
int parse_command(char command[], char *args[])
{
    int num_args = 0;
    char *token = strtok(command, " \n"); // Tokenize the command using space and newline as delimiters

    while (token != NULL && num_args < MAX_LINE / 2 + 1)
    {
        args[num_args] = token; // Store the argument
        num_args++;
        token = strtok(NULL, " \n");
    }
    
    args[num_args] = NULL; // Null-terminate the argument list
    return num_args;
}


/**
 * @brief The main function of a simple UNIX Shell. You may add additional functions in this file for your implementation
 * @param argc The number of arguments
 * @param argv The array of arguments
 * @return The exit status of the program
 */
int main(int argc, char *argv[])
{
    char command[MAX_LINE];       // the command that was entered
    char *args[MAX_LINE / 2 + 1]; // hold parsed out command line arguments
    int should_run = 1;           /* flag to determine when to exit program */

    // TODO: Add additional variables for the implementation.

    while (should_run)
    {
        printf("osh>");
        fflush(stdout);
        // Read the input command
        fgets(command, MAX_LINE, stdin);
        // Parse the input command
        int num_args = parse_command(command, args);

         if (num_args > 0)
    {
        if (strcmp(args[num_args - 1], "&") == 0)
        {
            // Background process requested
            args[num_args - 1] = NULL; // Remove the '&' from the arguments
            // TODO: Implement background process handling here
        }

        // Fork a child process
        pid_t pid = fork();

        if (pid == 0)
        {
            // Child process
            // Execute the command using execvp
            if (execvp(args[0], args) == -1)
            {
                perror("execvp");
            }
            exit(1); // Terminate the child process
        }
        else if (pid > 0)
        {
            // Parent process
            if (strcmp(args[num_args - 1], "&") != 0)
            {
                // Wait for the child process to complete (unless it's a background process)
                wait(NULL);
            }
        }
        else
        {
            // Fork failed
            perror("fork");
        }
    }
}
