// thiss is the main shell function that parses and runs the appropriate programs/commands
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "CS311_A01_2024394_sh_funcs.h"
#include "CS311_A01_2024394_built_in_funcs.h"
#include <fcntl.h>

void execute_command(char **args, int is_background)
{
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
    if (strcmp(args[0], "ps") == 0) 
    {
        ps2();
        return; 
    }
    if (strcmp(args[0], "kill") == 0) 
    {
        kill2(args);
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
    else if (pid > 0) 
    {
        
        if (is_background) 
        {
            for (int k = 0; k < MAX_PROCESSES; k++) 
            {
                if (process_list[k].is_active == 0) 
                {
                    process_list[k].pid = pid;
                    strncpy(process_list[k].name, args[0], 63);
                    process_list[k].is_active = 1;
                    break;
                }
            }
            
            printf("[Background process started with process ID: %d]\n", pid);
            
        } else 
        {
            waitpid(pid, NULL, 0);
        }
    } 
    else 
    {
        perror("fork() ERROR");
    }
}


void parse_and_execute(char *input)
{
    // zombie process remover
    int status;
    pid_t reaped_pid;
    while ((reaped_pid = waitpid(-1, &status, WNOHANG)) > 0) 
    {
        for (int k = 0; k < MAX_PROCESSES; k++) 
        {
            if (process_list[k].is_active == 1 && process_list[k].pid == reaped_pid) 
            {
                process_list[k].is_active = 0; 
                process_list[k].pid = 0;            
                process_list[k].name[0] = '\0';
                printf("[Background process %d (%s) finished]\n", reaped_pid, process_list[k].name);
                break;
            }
        }
    }

    // parsing


    int i = 0;
    char *raw_args[64]; 
    char *token = strtok(input, " \t");
    while (token != NULL && i < 63) {
        raw_args[i] = token;
        i++;
        token = strtok(NULL, " \t");
    }
    raw_args[i] = NULL; 

    if (raw_args[0] == NULL) {
        return;
    }

    // for debugging
   /*for (int ji = 0; ji <= i; ji ++)
    {
        printf("word number %d %s\n", ji, args[ji]);
    }*/
    
 

    // Execution 
    int start = 0; // Tracks where the current command chunk begins
    for (int j = 0; j <= i; j++) 
    {
        if (raw_args[j] == NULL || strcmp(raw_args[j], "&") == 0) 
        {
            int is_bg = 0;
            
            if (raw_args[j] != NULL && strcmp(raw_args[j], "&") == 0) 
            {
                is_bg = 1;
                raw_args[j] = NULL;
            }
            
        
            if (raw_args[start] != NULL) 
            {
                execute_command(&raw_args[start], is_bg);
            }
            
            start = j + 1; 
        }
    }
}
