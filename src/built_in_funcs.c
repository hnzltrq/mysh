#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "sh_funcs.h"
#include "built_in_funcs.h"


void cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "mysh: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("ERROR");
        }
    }
}


void pwd(void) {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("ERROR");
    }
}