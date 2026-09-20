// headerfile that contains functions that the shell runs to execute programs
#ifndef SH_FUNCS_H
#define SH_FUNCS_H

// all this does is execute the command as is required
void parse_and_execute(char *input);


// structure for proc information
typedef struct 
{
    pid_t pid;
    char name[64];
    int is_active; // 1 = active, 0 = done
} ProcessRecord;

#define MAX_PROCESSES 64
extern ProcessRecord process_list[MAX_PROCESSES]; 




#endif