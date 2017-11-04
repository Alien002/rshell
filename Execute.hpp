//
//  Execute.hpp
//  rshell
//
//  Created by Alic Lien on 11/2/17.
//
//

#ifndef Execute_hpp
#define Execute_hpp

#include <stdio.h>
#include "Command.hpp"

void buildV(vector<string>& v, Command& a){
    
    while(!a.qEmpty()){
        v.push_back(a.qFront());
        //cout <<v.back() <<endl;
    }
}

bool execute(vector<string>& a){
    char* args[100];                           //whitespace for echo cmd doesn't matter
    
    
    pid_t pid = fork();
    int status;
    for(int i = 0; i < a.size(); ++i){
        if(a.at(i) == "-q"){                        //program kill switch
            exit(1);
        }
            args[i] = (char*) a.at(i).c_str();
        
    }
    args[a.size()] = nullptr;
    
    
    
    
    if(pid < 0){
        cout <<"***ERROR: forking child process failed\n";
        exit(1);
    }
    else if(pid == 0){
        if(execvp(args[0], args) == -1){                 //prints out commands, and does not end program
            perror("execvp");
            return false;                               //error message if command isn't valid
        }
    }
    else{
        while(wait(&status) != pid){

        }
    }
    return true;
}




#endif /* Execute_hpp */
