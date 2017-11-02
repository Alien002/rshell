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
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "test.cpp"

using namespace std;

void inputCommands(vector<string>& cmds){
    cout <<"rshell$ ";
    string input = "";
    getline(cin, input);
    if(input == "-q"){
        exit(0);
    }
    boost::split(cmds,input,boost::is_any_of(" ,; "));          //with current parse, a whitespace/empty v.at(i) is created
    
    
    return;
}




int main(int argc, char** argv){
    while (1){
        //string input;
        vector<string> cmds;
        inputCommands(cmds);
    
//        cout <<cmds <<endl;
        for(int i = 0; i < cmds.size(); ++i){
            cout <<cmds.at(i) <<endl;
        }
        execute(cmds);
        
    }
    return 0;
}
