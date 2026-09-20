// thiss is the main shell function that parses and runs the appropriate programs/commands
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "sh_funcs.h"
#include "built_in_funcs.h"


void parse_and_execute(char *input)
{
    // parsing
    int i = 0;
    char *args[64]; // Array to hold up to 64 individual strings
    char *token = strtok(input, " \t");
    while (token != NULL && i < 63) 
    {
        args[i] = token;
        i++;
        token = strtok(NULL, " \t"); // Gets the next word
    }
    args[i] = NULL; // terminates the char array with a NULL as is needed for exec system calls 

    if (args[0] == NULL) // returns if the commands are empty
    {
        return;
    }

    // for debugging
   /*for (int j = 0; j <= i; j ++)
    {
        printf("word number %d %s\n", j, args[j]);
    }*/
    

    // Execution 

    // for built in commands (pwd, and cd)
    if (strcmp(args[0], "cd") == 0) {
        cd(args);
        return; 
    }
    
    if (strcmp(args[0], "pwd") == 0) {
        pwd();
        return; 
    }

    // for non nuilt in commands
    int pid = fork();

    if (pid == 0) {
        execvp(args[0], args);
        // the next two lines should not run, if they do print something bad has happened
        perror("ERROR"); 
        exit(1); 
    } 
    else if (pid > 0) {
        waitpid(pid, NULL, 0);
    } 
    else {
        perror("ERROR");
    }

}