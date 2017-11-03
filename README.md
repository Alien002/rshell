CS100 - Assignment 2
Team: Alic Lien, Daniel Li
Project: rShell C++ Program




================================================Summary================================================
    rShell C++ program that allows us to link multiple shell commands, and run it. The program uses
three operators: "; " which runs all code. "||" runs if lhs fails, rhs runs and vice versa. "&&" runs
if lhs runs, rhs runs, vice versa. As of testing so far, we can technically run more than 3 executables.
The "-q" command is used to exit the program.



================================================Bugs================================================
1. for cases where F && F; T, error message will be printed out twice for the second F.
2. there is a bug with git commit -m, the error message does not work with white space inside the 
    quotations. Will only work if "message_is_typed_like_this".
3. if #comment is entered by itself, program seg faults.

Last Debug: 11/3/2017 - 1:31 AM
No furthur bugs detected at the moment.
