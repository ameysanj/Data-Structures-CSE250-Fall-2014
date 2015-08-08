// ============================================================================
// main.cpp
// ~~~~~~~~
// author: hqn
// - main body of the edge counting program
// ============================================================================

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>   
#include <sys/time.h>
#include <map>   
#include <cstdlib> // for exit()

#include "term_control.h"
#include "error_handling.h"
#include "Lexer.h"
#include "algos.h"

using namespace std;

typedef void (*cmd_handler_t)(Lexer);

void vbaDispatcher(Lexer);
void sbaDispatcher(Lexer);
void bye(Lexer);

void prompt();

const char *usage_msg = "Usage: vba <file name>\n"
                        "       sba <file name>\n"
                        "       exit/quit/bye";

int main(int argc, char **argv) 
{
    if (argc != 1) 
        error_quit("edgecount doesn't take any argument");

    map<string, cmd_handler_t> commands;
    commands["vba"] = &vbaDispatcher;
    commands["sba"] = &sbaDispatcher;
    commands["quit"] = &bye;
    commands["exit"] = &bye;
    commands["bye"] = &bye;

    string line; Token tok; Lexer lexer;

    while (cin) {
        prompt(); 
        getline(cin, line); 
        lexer.set_input(line);

        if (!lexer.has_more_token()) continue;

        tok = lexer.next_token();
        if (tok.type == IDENT) {
            if (commands.find(tok.value) != commands.end()) {
                try {
                    struct timeval tv;
                    gettimeofday(&tv, NULL);     // mark start time
                    commands[tok.value](lexer);
                    struct timeval tv2;          // mark finish time
                    gettimeofday(&tv2, NULL);
                    ostringstream oss;
                    oss << left << setw(30) << fixed
                        << "seconds elapsed: " 
                        << double(tv2.tv_sec - tv.tv_sec) + 
                        double(tv2.tv_usec - tv.tv_usec)/1000000;
                    report(oss.str());          
                } catch (exception &e) {
                    error_return(e.what());
                }
                continue;
            }
        }
        note(usage_msg);
    }

    return 0; // 0 indicates 'success', this is a Unix thing
}

void vbaDispatcher(Lexer lex)
{
    Token tok;
    if (!lex.has_more_token())
        throw runtime_error(usage_msg);

    tok = lex.next_token();
    if (lex.has_more_token()) // 3rd token
        throw runtime_error(usage_msg);

    cout << vba(tok.value) << endl;
}

void sbaDispatcher(Lexer lex)
{
    Token tok;
    if (!lex.has_more_token())
        throw runtime_error(usage_msg);

    tok = lex.next_token();
    if (lex.has_more_token()) // 3rd token
        throw runtime_error(usage_msg);

    cout << sba(tok.value) << endl;
}

void bye(Lexer l) 
{
    if (l.has_more_token())
        throw runtime_error(usage_msg);
    else 
        exit(0);
}

void prompt()
{ 
    cout << term_cc(BLUE) << "> " << term_cc() << flush; 
}
