#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>


using namespace std;

bool execute(vector<string> a){                     //v.at(1) = echo ; v.at(2) = hello; v.at(3) = world;    another execute function needed for || operator
    char* args[a.size()];                           //whitespace for echo cmd doesn't matter
    
    
    pid_t pid = fork();
    int status;
    for(int i = 0; i < a.size(); ++i){
        if(a.at(i)=="nullptr"){
            args[i] = nullptr;
        }
        else{
            args[i] = (char*) a.at(i).c_str();
            //cout << a.at(i) <<endl;
        }
    }
    args[a.size()] = nullptr;
    
    

    
    if(pid < 0){
        cout <<"***ERROR: forking child process failed\n";
        exit(1);
    }
    else if(pid == 0){
        //cout <<"pid == 0" <<endl;
        if(execvp(args[0], args) == -1){                 //prints out commands, and does not end program
            perror("execvp");
            return false;                               //error message if command isn't valid
        }
        //cout <<"end2\n";
    }
    else{
        //cout <<"child\n" <<endl;
        while(wait(&status) != pid){
            //cout <<"child\n" <<endl;
        }
        
        //cout <<"end\n";
    }
    return true;
}

//Alpha test file, testing out how execvp works
/*
int main(int argc, char** argv){
    
    //ls -a; echo hello world;
    string ls = "ls";
    string b = "-a";
    vector <string> a;
    //vector <string> b;
    a.push_back(ls);
    a.push_back(b);
    //a.push_back("nullptr");

    execute(a);
    
    cout <<"program continued\n";

    a.clear();
    a.push_back("echo");
    a.push_back("hello world");
    
    execute(a);
    
    
    return 0;
}
*/

