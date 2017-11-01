#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <vector>

using namespace std;


//Alpha test file, testing out how execvp works
int main(int argc, char** argv){
    
    
    string ls = "ls";
    string dash_l = "-a";
    vector <string> a;
    a.push_back("ls");
    a.push_back("-a");
    a.push_back("nullptr");
    //a.push_back("echo hello world");
    
    a.push_back("-e");
    a.push_back("echo");
    a.push_back("hello world");
    a.push_back("nullptr");
    
    //a.push_back("");
    //a.push_back("/n");
    //a.push_back("echo hello world");
    char* args[a.size()];
    
    
    pid_t pid = fork();
    int status;
    for(int i = 0; i < a.size(); ++i){
        if(a.at(i)=="nullptr"){
            args[i] = nullptr;
        }
        else{
            args[i] = (char*) a.at(i).c_str();
        }
    }
    args[a.size()] = nullptr;
    
    
    if(pid < 0){
        cout <<"***ERROR: forking child process failed\n";
        exit(1);
    }
    else if(pid == 0){
        cout <<"pid == 0" <<endl;
        if(execvp(args[0], args) == -1){
            perror("exec");
        }
    }
    else{
        cout <<"child\n" <<endl;
        while(wait(&status) != pid){
            cout <<"child\n" <<endl;
        }
    }
    /*
    args[0] = (char*) ls.c_str();
    args[1] = nullptr; //(char*) dash_l.c_str();
    args[2] = nullptr;
    */
    
    
    
    
    
    
    
    
    
    return 0;
}
