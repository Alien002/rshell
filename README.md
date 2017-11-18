CS100 - Assignment 2
Team: Alic Lien, Daniel Li
Project: rShell C++ Program
Last edited: 11/17/2017 - 10:26 AM



=======================================Summary=======================================
    rShell C++ program that allows us to link multiple shell commands, and run it. The program uses
three operators: "; " which runs all code. "||" runs if lhs fails, rhs runs and vice versa. "&&" runs
if lhs runs, rhs runs, vice versa. As of testing so far, we can technically run more than 3 executables.
The "-q" command is used to exit the program.



=========================================Report======================================
11/3/2017 - 1:31 AM - Alic
1. for cases where F && F; T, error message will be printed out twice for the second F.
2. there is a bug with git commit -m, the error message does not work with white space inside the 
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



