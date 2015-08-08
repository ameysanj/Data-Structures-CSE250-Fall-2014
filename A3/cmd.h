// ============================================================================
// cmd.h
// ~~~~~
// author : hqn
// + Interface to the commands
// ============================================================================

#ifndef CMD_H_
#define CMD_H_

#include <string>
#include "Lexer.h"

/**
 * cmd_handler_t is a function pointer type, pointing to a function that takes
 * a string and returns nothing.
 */
typedef std::string (*cmd_handler_t)(const std::string&);

/**
 * -----------------------------------------------------------------------------
 *  TO BE IMPLEMENTED BY YOU
 *  check whether the given expression is well-formed according to 250HTML
 *  - tokenize expression into a stream of TAGs, BLANKs, and IDENTs
 *  - push & pop TAGs from a stack appropriately to see if they match
 *  - report one of the three errors if you see them
 *
 *  - there are three common types of errors you should try to handle:
 *    1. a token is invalid, i.e. expression where there's a < but no closing >
 *       in that case, return
 *       "INVALID TOKEN"
 *    2. a TAG is not found from the set of valid tags, such as
 *       <invalidtag>
 *       </invalidtag>
 *       <some thing weird>
 *       in that case, return
 *        "UNKNOWN TAG"
 *    3. the tags are valid but not nested correctly, here we have to use a
 *    stack to detect that. In that case, return
 *        "EXPRESSION NOT WELL-FORMED"
 * -----------------------------------------------------------------------------
 */
std::string validate(const std::string& expression);

/**
 * -----------------------------------------------------------------------------
 * TO BE IMPLEMENTED BY YOU
 *  display the expression correctly following the TAGs
 *  + if the expression is valid, return the expression with appropriate
 *    ASCII control codes inserted
 *  + if the expression is not valid, return the error string as in validate
 * -----------------------------------------------------------------------------
 */
std::string display(const std::string& expression);

#endif
