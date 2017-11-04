//
//  main.cpp
//  rshell - assignment 2
//
//  Created by Alic Lien & Daniel Li on 10/28/17.
//  Updated 11/3/2017 - Hotfix
//  Compiles via g++ main.cpp Command.cpp
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <vector>
#include <string>
#include <queue>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
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
        
        if(v.at(i) == "#" || (v.at(i) != string() && v.at(i).at(0) == '#')){
            i = v.size();
        }
        else{
            cmds.push(v.at(i));
        }
    }
    cmds.push("-0");        //last cmd
    return;
}



void buildExecutable(queue<string>& input, vector<Command> &v){  //builds executable into a package
    //cout <<"build executable\n";
    queue<string> temp;
    int sz = input.size();
    int i = 0;
    
    
    while(i != sz){
        temp.push(input.front());
        input.pop();

        
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


int main(int argc, char** argv){
    intro();
    
    while (1){
        vector<Command> executables;
        queue<string> input;
        
        inputCommands(input);
        
        buildExecutable(input, executables);
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
        
    }
    return 0;
}
