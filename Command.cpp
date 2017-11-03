//
//  Command.cpp
//  rshell
//
//  Created by Alic Lien on 11/2/17.
//
//

#include "Command.hpp"
#include <stdexcept>
//using namespace std;
//command object, stores queue of commands & flag

Command::Command() {}


Command::Command(queue<string> &a, string flag){
    this -> flag = flag;
    
    
    swap(cmds, a);              //clears queue/swaps contents
}


const string Command::getFlag(){
    return flag;
}


const string Command::qFront(){                                  //returns string and pops queue;
    if(cmds.empty()){
        throw std::out_of_range("out of range");
    }
    string temp = cmds.front();
    //cout <<"cmd qFront: " <<temp <<endl;
    cmds.pop();
    //cout <<"cmds.front(): " <<cmds.front() <<endl;
    return temp;
}

bool Command::qEmpty(){
    return cmds.empty();
}

int Command::qSize(){
    return cmds.size();
}

