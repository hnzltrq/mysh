#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
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