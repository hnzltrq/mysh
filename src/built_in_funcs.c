#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "sh_funcs.h"
#include "built_in_funcs.h"


void cd(char **args) {
    if (args[1] == NULL) { // if No argument given
        fprintf(stderr, "give a proper directory to change to!\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("ERROR");
        }
    }
}


void pwd(void) {
    char cwd[4096]; // the max size for a linux directory path is 4096 bytes
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("ERROR");
    }
}


void ps(void) 
{
    printf("PID\tCOMMAND\n");
    for (int k = 0; k < MAX_PROCESSES; k++) 
    {
        if (process_list[k].is_active == 1) 
        {
            printf("%d\t%s\n", process_list[k].pid, process_list[k].name);
        }
    }
}



void kill(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "kill requires a PID\n");
        return;
    }
    
    pid_t target_pid = atoi(args[1]); 
    
    if (kill(target_pid, SIGTERM) == 0) 
    {
        
        // deelttes required proc from the process information array
        for (int k = 0; k < MAX_PROCESSES; k++) 
        {
            if (process_list[k].is_active == 1 && process_list[k].pid == target_pid) 
            {
                
                process_list[k].is_active = 0;
                process_list[k].pid = 0;
                process_list[k].name[0] = '\0';
                
                printf("Process %d killed and expunged.\n", target_pid);
                break;
            }
        }
    } 
    else 
    {
        perror("kill() ERROR");
    }
}