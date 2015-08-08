// ============================================================================
// Lexer.h
// ~~~~~~~
// author : hqn
// - a simple lexical analyzer that scans the given input string for tokens
// - there are five types of tokens:
//   + BLANK:  a consecutive sequence of space characters 
//             which are ' ', '\r', '\n', and '\t'
//   + IDENT:  a sequence of non-blank characters that does not start with <
//   + TAG:    opening tag <sometag> or closing tag </sometag>
//   + ENDTOK: marks the end of the input string
//   + ERRTOK: means we are in an error state, for example, < without closing >
// ============================================================================

#ifndef LEXER_H_
#define LEXER_H_

#include <string>

enum token_types_t 
{ 
    BLANK,  // a consecutive sequence of space characters
    IDENT,  // a sequence of non-blank characters that does not start with <
    TAG,    // sequence of characters between < >, no escape
    ENDTOK, // end of string/file, no more token
    ERRTOK  // unrecognized token
};

/**
 * -----------------------------------------------------------------------------
 * When we define 
 *     Token tok;
 * we can access two properties of tok: 
 * - tok.type (which is one of BLANK, IDENT, TAG, ENDTOK, ERRTOK)
 * - tok.value (which is the content of the token)
 * -----------------------------------------------------------------------------
 */
class Token 
{
public:
    token_types_t type;
    std::string   value;

    Token(token_types_t tt=ENDTOK, std::string val="") : type(tt), value(val) {}
};

/**
 * -----------------------------------------------------------------------------
 * Typical usage of the Lexer class is as follows
 *
 * Lexer lex;
 * lex.set_input(somestring); // here somestring can be an expression
 * while (!lex.has_more_token) {
 *    Token tok = lex.next_token();
 *    if (tok.type == ERRTOK) {
 *       report_error(); // say throw an exception
 *    } else {
 *       do_something(tok);
 *    }
 * }
 *
 * -----------------------------------------------------------------------------
 */
class Lexer 
{
public:
    // constructor
    Lexer(std::string str="") {
        input_str = str; 
        cur_pos   = 0;
        in_err    = false;
    }

    // a couple of modifiers
    void set_input(std::string); // set a new input, 
    void restart();              // move cursor to the beginning, restart

    // a couple of accessors
    bool has_more_token();       // are there more token(s)?
    Token next_token();          // returns the next token

private:
    std::string input_str;  // the input string to be scanned
    size_t      cur_pos;    // current position in the input string
    bool        in_err;     // are we in the error state?
};

#endif // LEXER_H_
