//
//  main.cpp
//  rshell - assignment 2
//
//  Created by Alic Lien & Daniel Li on 10/28/17.
//  compiles via g++ main.cpp Command.cpp
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
//#include "test.cpp"
//#include "Command.cpp"
#include "Command.hpp"
#include "Execute.hpp"


// ls -a || touch main.cpp || echo rip
using namespace std;

//takes user input (getline), builds commands.
void inputCommands(queue<string>& cmds){
    //cout <<"input cmds\n";
    vector<string> v;
    cout <<"rshell$ ";
    string input;
    getline(cin, input);
    /*
    if(input == "-q"){                                          //occasionally requires -q to be typed twice for program to exit.
        exit(0);
    }
    */
    boost::split(v,input,boost::is_any_of(" ,; "));          //with current parse, a whitespace/empty v.at(i) is created
                                                                //git commit -m needs underscores for  ""
    for (int i = 0; i < v.size(); ++i){
        //cout <<v.at(i) <<endl;
        if(v.at(i) == "#" || v.at(i).at(0) == '#'){
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
        //cout <<"buildExe input: " <<input.front() <<" input size: " <<input.size() <<endl;               //if last input is ";" something messes up
        temp.push(input.front());
        input.pop();
        /*
        if(input.empty()){
            cout <<"input empty\n";
            return;
        }
        */
        
        if(input.front() == string()){
            input.pop();
            v.push_back(Command(temp, "; "));
            if(input.empty()){
                //cout <<"input .empty\n";
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
            //cout <<"else if\n";
            input.pop();
            v.push_back(Command(temp, ""));
            
            return;
        }
        //assuming new Command(temp, --) swaps filled temp queue with empty protected queue
    }
    
}


int main(int argc, char** argv){
    while (1){
        //string input;
        
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
                repeat = true;
                execute(lhs);
            }
            else{
                if(repeat){
                    execute(lhs);
                }
            }

        }
        
    }
    return 0;
}
