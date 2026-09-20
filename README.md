# mysh



## Issues 
- If a user tries to run a command which has more then 63 words (since the 64th string needs to be a NULL), the parsing will overflow and the program fail; presumably no commands that long are required.

- only the `pwd` and `cd` bash commands are supported, other commands such as aliases, manipulating the directory stack, and scritping are completely unsupported.

- cd command doesnt recognize commonly used short hands such as ~ for the home directory, etc. However the short hands for `..` being a directory up a level and `.` being the current directory are supported as they're built into the linux file system.

