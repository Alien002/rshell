CS100 - Assignment 2 <br />
Team: Alic Lien, Daniel Li <br />
Project: rShell C++ Program <br />
Last edited: 12/8/2017 - 8:21 PM <br />



## Summary

rShell program is a modified version of standard shell. The rShell is implemented through C++, and allows users the standard shell functions, and more. Standard single commands, and chained commands are implemented. Commenting is allowed within the shell. Additional functions include allowing users to ```test``` to see if a directory/file exists. File input/output redirection is another feature ported from regular shell.

## Usage

rShell allows:
1. Chaining commands via ```&&```, ```||```, ```;```.
2. Commenting in rshell is allowed via ```#```.
3. Users can check if a file exists via ```test -flag <path>``` or ```[ -flag <path> ]```
    flags:
    ```-e```	checks if the file/directory exists.
    ```-f```	checks if the file/directory exists and is a regular file.
    ```-d```	checks if the file/directory exists and is a directory.
4. File input/output is available for single cases.
    ```cat < <path>``` allows the shell to display all the text within the file
    ```<commands> > <path>``` and ```<commands> >> <path>``` prints anything that would display for the command into the specified file (if file does not exist, one is created).


## Report

```A collection of updates reports from the coding process```

11/3/2017 - 1:31 AM - Alic
1. (RESOLVED)for cases where F && F; T, error message will be printed out twice for the second F.
2. (RESOLVED/IMPLEMENTED) There is a bug with git commit -m, the error message does not work with white space inside the 
    quotations. Will only work if "message_is_typed_like_this". 
3. if #comment is entered by itself, program seg faults.


11/3/2017 - 9:01 PM - Daniel
1. Manually typing "echo A || echo B || echo C" in rshell will output
   A
   C
   while with the shell script, "echo A || echo B || echo C" will output
   A
   (multi_command.sh - Test #3)
   (manual output is correct, script output is wrong)
   
2. Manually typing "echo A || echo B; echo C" in rshell will output
   A
   while with the shell script, "echo A || echo B; echo C" will output
   A
   C
   (multi_command.sh - Test #5)
   (manual output is wrong, script output is correct)
   
3. Manually typing "echo A || echo B && echo C" in rshell will output
   A
   while with the shell script, "echo A || echo B && echo C" will output
   A
   C
   (multi_command.sh - Test #9)
   (manual output is correct, script output is wrong)
   
4. **Not sure if this counts as a bug**
   Manually typing "echo "||" && echo "&&" && echo ";"" will output
   "||"
   "&&"
   ";"
   while with the shell script, "echo "||" && echo "&&" && echo ";"" will output
   ||
   &&
   ;
   (multi_command.sh - Test #11)
   
5. exit.sh not working at the moment


11/16/2017 - 9:40 AM - Alic
1. rshell compiles and runs via. g++ main.cpp Command.cpp, not running properly for some reason with make file.

11/16/2017 - 10:43 AM - Alic
1. fixed make file problems, rshell executable now created correctly inside bin folder. Problem was with me updating main.cpp inside root folder, but not in the ./src/, thus g++ in root folder worked, but not via make file, as it took the .cpp from ./src/
2. make clean might need some fixing


11/17/2017 - 10:16 PM - Alic
1. Ran into some problems with our logic and thinking of the operators, fixed to correct logic for operators. Delayed program by several hours time. (refer to issues)
2. Parentheses work if it is the first thing encountered in line of commands. (refer to issues)
3. Test -flags and [-flag ] work in program.
4. Errors with multiple parentheses, could not implement nested parentheses at this time.d
5. Suggest converting vector of commands into a tree, will require code overhaul.
6. "" do not work when # is typed within it, due to # implementation location, might need fix

12/7/2017 - 3:42 AM - Alic
1. For some reason, dup2(test,1) creates an out of range error, without forking used, it quits the program, so I used forking to allow the program to continue.
    - in rshell, after typing say echo a > a.txt, blank lines continuously show up while pressing enter, disappears after typing ; followed by enter.
    - after typing enter the out of range error shows up in shell.
    - in a.txt, the output that shows up would be:
        a
        $ $ $ $ $ $
    - the dollar signs show up consecutively with the amount of enters pressed while in loop.
Currently not sure what is causing the out of range error, nor how to fix it, tried the dup2 process on a test.cpp file, seems to work without problem.

12/7/2017 - 9:03 PM - Alic
1. Implemented cat < filename
2. Fixed the dup out of range error
3. < and >/>> work for single cases
