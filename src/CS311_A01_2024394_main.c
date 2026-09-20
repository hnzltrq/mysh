#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linenoise.h"
#include "CS311_A01_2024394_sh_funcs.h"


ProcessRecord process_list[MAX_PROCESSES] = {0};


int main(void)
{
    char * command;

    while ((command = linenoise("What be thy command? >")) !=NULL) // loops runs continosuly reading and executing commands
    {

        // printf("input: %s\n", command); // Meant to be used for debugging

        if (strcmp (command, "exit")==0) // exits shell
        {
            free (command); // frees space allocated for the string
            break;
        }

        parse_and_execute(command); // does the actual work
        
    }

    return 0;
}