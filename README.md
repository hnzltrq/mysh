# mysh
<sub><sup>Written by M. Hanzla Tariq (2024934)</sup></sub>

A simple UNIX shell written in C. Made as a course project. (CS331 at GIKI). 


## Build Instructions
You will need gcc 16.0.0 or higher to compile the C23 code, along with make version 4.0.0 or higher.

Technically nothing here is C23 specific (no bools, nullptrs or anything newer), however it was compiled and run on my system with C23 and tested with that as well, if your version of the GNU GCC compiler does not support GNU C23, change the `-std=gnu23` flag in the make file to `-std=gnu11` (C11 with GNU/POSIX-Linux extensions). Hopfully nothing will break.


To build the project, simply run:
```bash
make
```
Which will then build the `mysh` binary that can be run as a program.

## Features 

- Standard GNU/Linux commands are fully supported (ls, grep, mkdir, etc)
- I/O redirection with the `>>`, `>`, `<` operators are also supported. (The here document opeartor `<<` is not supported.)
- `cd` and `pwd` are built-in.
- Supports pipelining with the `|` opeartor.
- Uses the [linenoise](https://github.com/antirez/linenoise) library for clean user input.
- Run processes in the background with the `&` operator.
- Has a custom `ps` command that tracks currently running processes made by the shell.
- Has a custom `kill` command that kills processes made by the shell.

## Limitations
- If a user tries to run a command which has more then 63 words (since the 64th string needs to be a NULL), the parsing will overflow and the program fail; presumably no commands that long are required.
- A total maximum of 64 background processes can be supported. If the number of processes exceeds this the program will misbehave.
- only the `pwd` and `cd` bash commands are supported, other commands such as aliases, manipulating the directory stack, and scritping, amongst others are completely unsupported.
- `cd ` command doesnt recognize commonly used short hands such as `~` for the home directory, etc. However the short hands for `..` being a directory up a level and `.` being the current directory are supported as they're built into the linux file system.
- It is entirely possible that if the user terminates the running program using the `ctrl+C` short cut, some memory might be left unfreeed, however most Operating systems should be able to deal with that. I think. 
- The way pipelining is implemented, it will completey bypass the built in `cd` and `pwd` functions. 
- occationally a command run with `sudo` fails to recognize root password and freezes the shell.
- The shell doesn't support the AND operator `&&`, rather its functionality can be achieved by stringing together commands with the `&` operator. The first command will run in the background followed by the second command. If there are more then one commands being strung together all but the last one will run in the background.


