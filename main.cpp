//
//  main.cpp
//  rshell
//
//  Created by Alic Lien & Daniel Li on 10/28/17.
//
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
#include "test.cpp"



// ls -a || touch main.cpp || echo rip
using namespace std;

void inputCommands(queue<string>& cmds){
    vector<string> v;
    cout <<"rshell$ ";
    string input;
    getline(cin, input);
    if(input == "-q"){                                          //occasionally requires -q to be typed twice for program to exit.
        exit(0);
    }
    boost::split(v,input,boost::is_any_of(" ,; "));          //with current parse, a whitespace/empty v.at(i) is created
                                                                //git commit -m needs underscores for  ""
    for (int i = 0; i < v.size(); ++i){
        //cout <<"inputcommands v.at(i): " <<v.at(i) <<endl;
        cmds.push(v.at(i));
        //cout <<"cmds.back(): " <<cmds.back() <<endl;
    }
    cmds.push("");
    return;
}




int main(int argc, char** argv){
    while (1){
        //string input;
        queue<string> cmds;
        inputCommands(cmds);
        
        vector<string> exe;
        
        int queueSize = cmds.size();                    //pass cmds and exe into separate function
        
        //daniel added this
        bool check;
        
        for(int i = 0; i < queueSize; ++i){         // works for "; " operator so far
            exe.push_back(cmds.front());
            cmds.pop();
            
            if(cmds.front() == "" || cmds.front() == "||" || cmds.front() == "&&"){
                if(cmds.front() == "||"){
                    //set flag
                }
                else if(cmds.front() == "&&"){
                    //set flag
                }
                cmds.pop();
                check = execute(exe); //daniel added this line and replaced !execute(exe) with !check (for efficiency...?)
                if (!check){
                    cout <<"command does not work!!\n";
                }
                exe.clear();
                i = 0;
                queueSize = cmds.size();
            }
            //daniel did || case NEED TO TEST
            else if(cmds.front() == "||"){
                if (check) { //PREVIOUS SUCCEEDED
                    cmds.pop();
                    while (!cmds.empty() || (cmds.front() != "" || cmds.front() != "||" || cmds.front() != "&&") ){ //as long as cmds not empty we search for next command after the one that we skip
                        cmds.pop();
                    }
                }
                else { //PREVIOUS FAILED
                    //copy paste from ; case
                
                    cmds.pop();
                    check = execute(exe); //daniel added this line and replaced !execute(exe) with !check (for efficiency...?)
                    if (!check){
                        cout <<"command does not work!!\n";
                    }
                    exe.clear();
                    i = 0;
                    queueSize = cmds.size();
                }
            }
/*
            if(cmds.front() == "||"){
                //check prev command succeeds or fails
                if succeeds {
                    //copy code from ;
                }
                else fails {
                    //search function for next ( && /|| /"" )
                    //maybe popfront until it shows up ? idk
                
                }
            }
 */
            
            
            
            //cout <<"exe.at(i): " <<exe.at(i) <<endl;
        
        //execute(cmds);
        }
        }
    return 0;
}
