//
//  main.cpp
//  rshell - assignment 3
//
//  Created by Alic Lien & Daniel Li on 10/28/17.
//  Updated 11/17/2017
//
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
    //cout <<"!!!!!Dev Mode!!!!!\n";
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
    for (unsigned i = 0; i < v.size(); ++i){
        
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
        //cout <<input.front() <<endl;
        //check input.front if its a test case.
        if(input.front() == "[" || input.front() == "test"){

            isTest(temp, test, input);
            
        }
        else{   //normal commands
            if(input.front().at(0) == '\"'){
                //cout <<"is quote called" <<endl;
                //input.front().erase(input.front().at(0));
                string isQuote = string();
                do{
                   // cout <<"while" <<endl;
                    //input.front().erase(input.front().back()-1);
                    isQuote += input.front();
                    
                    if(input.front().back() == '\"'){
                        break;
                    }
                        
                    isQuote += " ";
                    
                    if(!input.empty()){
                        input.pop();
                    }
                    
                }while(isQuote.back() != '\"');
                
                
                //isQuote += input.front();
                
                if(!input.empty()){
                    input.pop();
                }
                
                //cout <<isQuote <<endl;
                isQuote.erase(isQuote.begin());
                isQuote.erase(isQuote.size() - 1);
                //cout <<isQuote <<endl;
                temp.push(isQuote);
            }
            else{
                temp.push(input.front());
                input.pop();
            }
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

//////EXECUTE PARENTHESES
bool executeP(vector<Command> executables, unsigned &num) {          // change to bool function
    vector<string> lhs;
    bool repeat = true;
    bool case1 = false;
    bool case2 = false;
    bool case3 = false;
    string flg1;
    //single command.
    if(executables.size() == 1) {
        buildV(lhs, executables.at(0));
        
        if(execute(lhs)){
            return true;
        }
        else{
            return false;
        }
        //repeat = false;
    }
    
    
    for(; num < executables.size(); ++num){
        //cout <<"for loop \n";
        repeat = execute(lhs);
        
        //while(lhs.at(lhs.size()-1).at(lhs.at(lhs.size()-1).size()-1) != ')'){
        
        bool deleted = false;
        while(!deleted) {
            if(lhs.at(lhs.size()-1).at(lhs.at(lhs.size()-1).size()-1) == ')') {
                lhs.at(lhs.size()-1).erase(lhs.at(lhs.size()-1).size()-1);
                deleted = true;
            }
            
            
            lhs.clear();
            buildV(lhs, executables.at(num));
            
            if(num > 0){
                flg1 = executables.at(num - 1).getFlag();
            }
            else{
                flg1 = executables.at(0).getFlag();
            }
            if(flg1 == "&&" && repeat){
                //cout <<"flg = &&\n";
                case1 = execute(lhs);
            }
            
            else if(flg1 == "||" && !repeat){
                //cout <<"flg = ||\n";
                case2 = execute(lhs);
            }
            
            else if(flg1 == "; "){
                //cout <<"flg = ;\n";
                case3 = execute(lhs);
            }
        }
    }
    
    if(case1 || case2 || case3){
        return true;
    }					
    return false;
}

//Executes functions stored in Command object
bool executeA(vector<Command> executables){          // change to bool function
    vector<string> lhs;
    
    bool repeat = true;
    //bool case1 = false; //will set to true if one case of || was true
    bool inPar = false;
    bool inParRep = false;
    bool close = false;
    //int a = 0;
    
    string flg1;
    //single command.
    if(executables.size() == 1) {
        buildV(lhs, executables.at(0));
        
        if(execute(lhs)){
            return true;
        }
        else{
            return false;
        }
        //repeat = false;
    }
    
    
    for(unsigned i = 0; i < executables.size(); ++i){
        
        if(i > 0){
            flg1 = executables.at(i - 1).getFlag();
        }
        else{
            flg1 = executables.at(0).getFlag();
        }
        
        //cout <<flg1 <<endl;
        lhs.clear();
        buildV(lhs, executables.at(i));
        
        if(lhs.at(0).at(0) == '('){   //if open par, delete open "("
            
            //cout <<"open P\n";
            lhs.at(0).erase(lhs.at(0).begin()); //deletes it
            inPar = true;                       //flags in par as true
                
            //++a;
        }
        else if(lhs.at(lhs.size()-1).at(lhs.at(lhs.size()-1).size()-1) == ')'){ //close par
            
            lhs.at(lhs.size()-1).erase(lhs.at(lhs.size()-1).size()-1);          //deletes close par
            close = true;                                                       //notifies after running that par has closed, line 360
        }
        //do not touch//
        if(i == 0){
            repeat = execute(lhs);
            if(inPar){
                inParRep = repeat;
            }
            continue;
        }
        
        //repeat = whats in the parentheses)
        /*
        if(inPar && i != 0){
            cout <<"inPar && i != 0\n";
            repeat = !inParRep;
            cout << repeat <<endl;
        }
        else if(!inPar){
            //repeat = inParRep;
        }
        */
        
        if(inPar){
            //cout <<"inPar" << endl;
            repeat = inParRep;
        }
        
        
        if(flg1 == "&&" && repeat){
            //cout <<"flg = &&\n";
            if(inPar){
                if(execute(lhs)){
                    inParRep = true;
                }
                else{
                    inParRep = false;
                }
            }
            else{
                repeat = execute(lhs);
            }
        }
        else if(flg1 == "||" && !repeat){
           // cout <<"flg = ||\n";
            
            if(inPar){
                
                inParRep = execute(lhs);
                
            }
            else{
                repeat = execute(lhs);
                
            }
            //repeat = execute(lhs);
        }
        else if(flg1 == "; " && repeat){
            //cout <<"flg = ;\n";
            //execute(lhs);
            inParRep = true;
            repeat = execute(lhs);
        }
        
        if(close){                              //knows that par is close
            //cout <<"close P\n";
            inPar = false;
            repeat = inParRep;
            close = false;
        }
        
        
        
    }
    
    return repeat;
}
/*
bool boundExe(vector<string> lhs){
    
}
*/


int main(int argc, char** argv){
    intro();
    
    while (1){
        queue<string> input;
        vector<Command> executables;
        
        inputCommands(input);
        
        buildExecutable(input, executables);
        
        executeA(executables);
    }
    return 0;
}
