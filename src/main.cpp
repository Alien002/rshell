//
//  main.cpp
//  rshell - assignment 2
//
//  Created by Alic Lien & Daniel Li on 10/28/17.
//  Updated 11/16/2017 -
//  Compiles via g++ main.cpp Command.cpp
//

#include <iostream>
#include <vector>
#include <string>
#include <queue>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <sys/types.h>
#include <sys/stat.h>

#include "Command.hpp"
#include "Execute.hpp"


// ls -a || touch main.cpp || echo rip
using namespace std;

void intro(){
    cout <<"----------------rShell cmds----------------\n"
         <<"Connectors: \n"
         <<"\"||\" - will run second cmd if first fails.\n"
         <<"\"&&\" - will run second cmd if first runs.\n"
         <<"\"; \" - will always run next command.\n"
         <<"type -q as a shell command to quit rShell.\n"
         <<"-------------------------------------------\n";
    cout <<"!!!!!Dev Mode!!!!!\n";          
    return;
}

//takes user input (getline), builds commands.
void inputCommands(queue<string>& cmds){
    vector<string> v;
    cout <<"rshell$ ";
    string input;
    getline(cin, input);

    boost::split(v,input,boost::is_any_of(" ,; "));          //with current parse, a whitespace/empty v.at(i) is created
                                                                //git commit -m needs underscores for  ""
    for (int i = 0; i < v.size(); ++i){
        
        if(v.at(i) == "#" || (v.at(i) != string() && v.at(i).at(0) == '#')){        //checks for comment #
            i = v.size();
        }
        else{
            cmds.push(v.at(i));
        }
    }
    cmds.push("-0");        //last cmd
    return;
}

//handles the test command cases, uses stat.
void isTest(queue<string>& temp, queue<string>& test, queue<string>& input){
    input.pop();
    
    if(input.front() != "-e" && input.front() != "-f" && input.front() != "-d"){
        
        test.push("-e");
        test.push(input.front());           //assuming input.front is a check
        input.pop();
    }
    else{           //assumine is flag
        test.push(input.front());       //push flag
        input.pop();
        test.push(input.front());       //push file path
        input.pop();
    }
    
    if(input.front() == "]"){
        input.pop();
    }
    
    //check flag, an
    if(test.front() == "-e"){
        test.pop();
        //cout <<"-e flag" <<endl;
        struct stat st;
        if(stat(test.front().c_str(), &st) == 0){       //if true move on
            cout <<"True" <<endl;
            //temp.push("echo");
        }
        else{
            cout <<"False" <<endl;
            temp.push("la");
        }
        
    }
    else if(test.front() == "-f"){
        test.pop();
        //cout <<"-f flag" <<endl;
        struct stat st;
        stat(test.front().c_str(), &st);
        
        if(S_ISREG(st.st_mode)){                    //if true move on
            cout <<"True" <<endl;
            
        }
        else{
            cout <<"False" <<endl;
            temp.push("la");
        }
    }
    else if(test.front() == "-d"){
        test.pop();
        //cout <<"-d flag" <<endl;
        struct stat st;
        stat(test.front().c_str(), &st);
        
        if(S_ISDIR(st.st_mode)){                    //if true move on
            cout <<"True" <<endl;
            
        }
        else{
            cout <<"False" <<endl;                  //if false throw junk into temp queue to flag as failed for cmds
            temp.push("la");
        }
    }
    else{       //hopefully we never reach here
        cout <<"This isn't suppose to happen, how did you get here, who are you, please leave." <<endl;
        exit(1);
    }
    
    /*
     while(!test.empty()){                                       //used to check test queue strings.
     cout <<"test input front: " <<test.front() <<endl;
     test.pop();
     }
    */
    
    return;
}


//builds executable into a Command object, and
void buildExecutable(queue<string>& input, vector<Command> &v){
    //cout <<"build executable\n";
    queue<string> temp;
    queue<string> test; //only used for test
    
    int sz = input.size();
    int i = 0;
    
    
    while(i != sz){
        //check input.front if its a test case.
        if(input.front() == "[" || input.front() == "test"){

            isTest(temp, test, input);
            
            
        }
        else{   //normal commands
            temp.push(input.front());
            input.pop();
        }
        
        
        
        //connectors check
        if(input.front() == string()){
            input.pop();
            v.push_back(Command(temp, "; "));
            if(input.empty()){
                return;
            }
            ++i;
        }
        else if(input.front() == "&&"){
            input.pop();
            v.push_back(Command(temp, "&&"));
            ++i;
        }
        else if(input.front() == "||"){
            input.pop();
            v.push_back(Command(temp, "||"));
            ++i;
        }
        else if(input.front() == "-0"){
            input.pop();
            v.push_back(Command(temp, ""));
            
            return;
        }
    }
}

//Executes functions stored in Command object
void execute(vector<Command> executables){
    vector<string> lhs;
    vector<string> rhs;
    
    bool repeat = true;
    
    string flg1, flg2;
    if(executables.size() > 1){
        flg1 = executables.at(0).getFlag();
        flg2 = executables.at(1).getFlag();
    }
    else{
        execute(lhs);
        repeat = false;
    }
    for(unsigned i = 0; i < executables.size(); ++i){
        if(repeat && i != 0){
            flg1 = flg2;
            lhs = rhs;
            rhs.clear();
        }
        else if(!repeat){
            flg1 = flg2;
        }
        else{
            lhs.clear();
            rhs.clear();
            
        }
        buildV(lhs, executables.at(i));
        
        if(executables.size() == 1){
            execute(lhs);
        }
        
        if(flg1 == "&&"){
            
            if(repeat){
                if(execute(lhs)){
                    
                }
                else{
                    repeat = false;
                    
                }
            }
            else{
                ++i;            //skips rhs if fail
                
            }
        }
        else if(flg1 == "||"){
            if(repeat){
                if(!execute(lhs)){
                    
                    
                }
                else{
                    repeat = false;
                    
                }
            }
            else{
                repeat = true;
                
            }
            
            
        }
        else if(flg1 == "; "){
            if(repeat){
                execute(lhs);
            }
        }
        else{
            if(repeat){
                execute(lhs);
                repeat = false;
            }
        }
        
    }
    return;
}



int main(int argc, char** argv){
    intro();
    
    while (1){
        queue<string> input;
        vector<Command> executables;
        
        inputCommands(input);
        
        buildExecutable(input, executables);
        
        execute(executables);
    }
    return 0;
}
