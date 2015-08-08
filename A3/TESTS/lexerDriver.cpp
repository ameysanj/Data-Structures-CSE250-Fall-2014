// lexerDriver.cpp
#include <iostream>
#include "Lexer.h"

using namespace std; // BAD PRACTICE

int main() 
{
    string line;
    int i;

    Token tok; Lexer lexer;
    while (getline(cin, line)) // Ctrl-Z/D to quit!
    { 
        cout << "Enter an expression to tokenize: \n> ";
        lexer.set_input(line);
        while (lexer.has_more_token()) {
            tok = lexer.next_token();
            switch (tok.type) {
                case TAG:
                    if (tok.value[0] != '/') 
                        cout << "OPEN TAG: " << tok.value << endl;
                    else
                        cout << "CLOSE TAG: " << tok.value.substr(1) << endl;
                    break;
                case IDENT:
                    cout << "IDENT: " << tok.value << endl;
                    break;
                case BLANK:
                    cout << "BLANK: " << tok.value << endl;
                    break;
                case ERRTOK:
                    cout << "Syntax error on this line\n";
                    break;
                default:
                    break;
            }
        }
    }
    return 0;
}
