
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
     int arg_count = 0;
    char *token = strtok(command, " \n"); // Tokenize the command by space and newline

    while (token != NULL)
    {
        args[arg_count] = token;
        arg_count++;
        token = strtok(NULL, " \n");
    }

    args[arg_count] = NULL; // Null-terminate the argument list
    return arg_count;
}

// TODO: Add additional functions if you need

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
            // Check for the "exit" command
            if (strcmp(args[0], "exit") == 0)
            {
                should_run = 0; // Exit the shell
            }
            else
            {
                // Fork a child process
                pid_t pid = fork();

                if (pid == 0) // Child process
                {
                    // Execute the command in the child process
                    if (execvp(args[0], args) == -1)
                    {
                        perror("execvp"); // Print an error message if execvp fails
                        exit(EXIT_FAILURE);
                    }
                }
                else if (pid > 0) // Parent process
                {
                    int status;
                    // Wait for the child process to finish unless the command includes "&"
                    if (args[num_args - 1] != NULL && strcmp(args[num_args - 1], "&") != 0)
                    {
                        waitpid(pid, &status, 0);
                    }
                }
                else
                {
                    perror("fork"); // Print an error message if fork fails
                }
            }
        }
    }
    return 0;
}
