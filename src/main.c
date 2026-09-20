#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linenoise.h"
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    char * command;

    while ((command = linenoise("What be ye commmand> ")) !=NULL)
    {

        // printf("input: %s\n", command); // Meant to be used for debugging

        if (command[0] == '\0')
        {
            free (command);
            break;
        }
        
    }
}