# mysh



## Issues 
- If a user tries to run a command which has more then 63 words (since the 64th string needs to be a NULL), the parsing will overflow and the program fail; presumably no commands that long are required.

