#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linenoise.h"
#include "sh_funcs.h"

int main(void)
{
    char * command;

    while ((command = linenoise("What be ye commmand> ")) !=NULL) // loops runs continosuly reading and executing commands
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