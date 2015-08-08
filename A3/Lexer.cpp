// ============================================================================
// Lexer.cpp
// ~~~~~~~~~
// author : hqn
// - implementation of Lexer interface
// ============================================================================

#include <iostream>
#include <cctype>   // for isspace(.)
#include "Lexer.h"

using namespace std;

Token Lexer::next_token() 
{
    Token tok(ERRTOK, "");
    if (in_err)
        return tok;

    tok.type = ENDTOK;
    tok.value = "";

    size_t last_pos;
    if (has_more_token()) {
        last_pos = cur_pos;
        if (input_str[cur_pos] == '<') {
            cur_pos++;
            while (cur_pos < input_str.length() && input_str[cur_pos] != '>')
                cur_pos++;
            if (cur_pos < input_str.length()) {
                tok.type = TAG;
                tok.value = input_str.substr(last_pos+1, cur_pos-last_pos-1);
                cur_pos++; // move past the closing >
            } else {
                in_err = true;
                tok.type = ERRTOK;
                tok.value = "";
                cur_pos = last_pos; // points to location of error
            }
        } else if (isspace(input_str[cur_pos])) {
            while (isspace(input_str[++cur_pos]));
            tok.type = BLANK;
            tok.value = input_str.substr(last_pos, cur_pos-last_pos);
        } else {
            while (cur_pos < input_str.length() &&
                   !isspace(input_str[cur_pos]) &&
                   input_str[cur_pos] != '<') 
                cur_pos++;
            tok.type  = IDENT;
            tok.value = input_str.substr(last_pos, cur_pos-last_pos);
        }
    }
    return tok;
}

void Lexer::set_input(string str) 
{
    input_str = str;
    restart();
}

bool Lexer::has_more_token() 
{
    return (cur_pos < input_str.length());
}

void Lexer::restart() 
{
    cur_pos = 0;
    in_err = false;
}
