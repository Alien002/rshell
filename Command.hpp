//
//  Command.hpp
//  rshell
//
//  Created by Alic Lien on 11/2/17.
//
//

#ifndef Command_hpp
#define Command_hpp

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

using namespace std;

class Command{
  protected:
    
    queue<string> cmds;
    string flag;
    
  public:
    Command();
    Command(queue<string> &a, string flag);
    
    const string getFlag();
    const string qFront();
    
    int qSize();
    bool qEmpty();
    
    //void displayCmds();
};




#endif /* Command_hpp */
