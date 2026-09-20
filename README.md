# mysh
A simple UNIX shell written in C. Made as a course project. 


# Build Instructions
You will need gcc 16.0.0 or higher to compile the C23 code, along with make version 4.0.0 or higher.
To build the project, simply run:
```bash
make
```
Which will then build the `mysh` binary that can be run as a program.

## Features 

- Standard GNU/Linux commands are fully supported (ls, grep, mkdir, etc)
- I/O redirection with the `>>`, `>`, `<` operators are also supported.
- `cd` and `pwd` are built-in.
- Uses the [linenoise](https://github.com/antirez/linenoise) library for clean user input.


## Issues 
- If a user tries to run a command which has more then 63 words (since the 64th string needs to be a NULL), the parsing will overflow and the program fail; presumably no commands that long are required.
- only the `pwd` and `cd` bash commands are supported, other commands such as aliases, manipulating the directory stack, and scritping, amongst others are completely unsupported.
- cd command doesnt recognize commonly used short hands such as ~ for the home directory, etc. However the short hands for `..` being a directory up a level and `.` being the current directory are supported as they're built into the linux file system.
- It is entirely possible that if the user terminates the running program using the `ctrl+C` short cut, some memory might be left unfreeed, however most Operating systems should be able to deal with that. I think. 