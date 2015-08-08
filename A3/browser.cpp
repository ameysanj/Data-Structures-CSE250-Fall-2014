// ============================================================================
// browser.cpp
// author: hqn
// - a command line interface for validating and displaying 250HTML expressions
// usage: browser
// > validate [250HTML expression]
// > display [250HTML expression]
// > exit
// where validate checks whether the expression is well-formed
// and display prints the expression to the screen
// ============================================================================

#include <iostream>
#include <string>   
#include <map>   
#include <cstdlib>

#include "term_control.h"
#include "error_handling.h"
#include "Lexer.h"
#include "cmd.h"

using std::cout;
using std::cin;
using std::string;
using std::map;
using std::endl;

void prompt() 
{ 
    cout << term_fg(BLUE) << "> " << term_fg() << std::flush; 
}

string bye(const string& s) 
{
    if (!s.empty())
        return "Just type 'exit' by itself";
    exit(0);
}

int main(int argc, char **argv) 
{
    if (argc != 1) 
        error_quit("Browser doesn't take any argument");
    cout << "250HTML Browser and Validator, By HQN\n";

    string usage_msg = "Usage: validate [line to be validated]\n"
                       "       display [line following 250html format]\n"
                       "       exit/quit/bye";

    map<string, cmd_handler_t> commands;
    commands["validate"] = &validate;
    commands["display"]  = &display;
    commands["quit"]     = &bye;
    commands["exit"]     = &bye;
    commands["bye"]      = &bye;

    string line; 
    Token tok; 
    Lexer lexer;

    while (cin) {
        prompt(); 
        string command, therest;
        cin >> command;
        getline(cin, therest);

        if (commands.find(command) != commands.end()) {
            cout << commands[command](therest) << endl;
            continue;
        }
        note(usage_msg);
    }
    return 0;
}
