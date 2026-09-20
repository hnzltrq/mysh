// thiss is the main shell function that parses and runs the appropriate programs/commands
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "sh_funcs.h"
#include "built_in_funcs.h"
#include <fcntl.h>


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
   /*for (int ji = 0; ji <= i; ji ++)
    {
        printf("word number %d %s\n", ji, args[ji]);
    }*/
    

    // Execution 


    // scanning and implementing for pipelining 

    int pipe_index = -1;
    
    // searhcing for |
    for (int j = 0; args[j] != NULL; j++) 
    {
        if (strcmp(args[j], "|") == 0) 
        {
            pipe_index = j;
            break;
        }
    }

    if (pipe_index != -1) // only runs if a pipe is found
    { 
        
        args[pipe_index] = NULL; 
        
        char **cmd1 = args; // command 1                
        char **cmd2 = &args[pipe_index + 1]; // comand 2   

        int pipefd[2];
        
        if (pipe(pipefd) == -1) 
        {
            perror("ERROR: pipe failure");
            return;
        }

        // left side
        pid_t pid1 = fork();
        if (pid1 == 0) 
        {
            dup2(pipefd[1], STDOUT_FILENO); 
            
            close(pipefd[0]);
            close(pipefd[1]);

            execvp(cmd1[0], cmd1);
            perror(cmd1[0]);
            exit(1);
        }

        // right side
        pid_t pid2 = fork();
        if (pid2 == 0) 
        {
            
            dup2(pipefd[0], STDIN_FILENO);
            
            // Close both ends
            close(pipefd[0]);
            close(pipefd[1]);

            execvp(cmd2[0], cmd2);
            perror(cmd2[0]);
            exit(1);
        }

        close(pipefd[0]);
        close(pipefd[1]);

        waitpid(pid1, NULL, 0);
        waitpid(pid2, NULL, 0);
        
        return; 
    }

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

        // input redirection if >, >> or <, << show up
        for (int j = 0; args[j] != NULL; j++) 
        {
            
            // Output Redirection 

            // overwrite
            if (strcmp(args[j], ">") == 0) 
            {
                
                int fd = open(args[j+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                dup2(fd, STDOUT_FILENO); 
                close(fd);               
                args[j] = NULL;         
                break;
            }
            
            // appending
            else if (strcmp(args[j], ">>") == 0) 
            {
                int fd = open(args[j+1], O_WRONLY | O_CREAT | O_APPEND, 0644);
                dup2(fd, STDOUT_FILENO);
                close(fd);
                args[j] = NULL;
                break;
            }
            
            // Input Redirection

            else if (strcmp(args[j], "<") == 0) 
            {
                int fd = open(args[j+1], O_RDONLY);
                if (fd < 0) { // if file not opened
                    perror(args[j+1]); 
                    exit(1);
                }
                dup2(fd, STDIN_FILENO); 
                close(fd);
                args[j] = NULL;
                break;
            }
        }

        execvp(args[0], args);
        // the next two lines should not run, if they do print something bad has happened
        perror("exec() ERROR"); 
        exit(1); 
    } 
    else if (pid > 0) {
        waitpid(pid, NULL, 0);
    } 
    else {
        perror("fork() ERROR");
    }

}