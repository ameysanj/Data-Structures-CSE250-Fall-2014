// ============================================================================
// cmd.cpp
// ~~~~~~~
// author : Amey S. Mahajan 
// - implement the two main commands: validate and display
// - this is the only file you can modify and submit
// ============================================================================
#include <iostream>
#include <sstream>
#include <stack>
#include <map>
#include "cmd.h"
#include "Lexer.h" 
#include "term_control.h"
#include "error_handling.h"
using namespace std;
typedef string (* cmd_handler)(term_colors_t); 
/**
 * -----------------------------------------------------------------------------
 *  check whether the given expression is well-formed and print it out
 *  - if it is NOT well-formed, return one of the three error messages:
 *     "INVALID TOKEN"
 *     "EXPRESSION NOT WELL-FORMED"
 *     "UNKNOWN TAG"
 *  - if it is well-formed, return the string to be printed, with control codes
 *    inserted properly at the right places 
 * -----------------------------------------------------------------------------
 */
string display(const string& expression) 
{
	string displayString = validate(expression);	
	Lexer lex;
	Token tok;
	lex.set_input(expression);
	map<string,term_colors_t> displayMap; 	
	map<string,term_attrib_t> displayMapAttr;
	string tagValue= "";
	string Return ="";
	string attribValue;
	string Ident ="";
	stack<string> st;
	stack<string> st_att;
	displayMap["red"] = RED;
	displayMap["cyan"] = CYAN;
	displayMap["blue"] = BLUE;
	displayMap["magenta"] = MAGENTA;
	displayMap["yellow"] = YELLOW;
	displayMap["green"] = GREEN;
	displayMapAttr["dim"]=DIM;
	displayMapAttr["bright"]=BRIGHT;
	displayMapAttr["underline"]=UNDERLINE;	
	if(displayString=="VALID"){
		while(lex.has_more_token()){
			tok = lex.next_token();
			if(tok.type==TAG && tok.value[0]!='/'){
				if(tok.value!="dim" && tok.value!="bright"&& tok.value!="underline"){
					tagValue=tok.value;
					st.push(tagValue);
				}
				else{
						attribValue = tok.value;
						st_att.push(attribValue);
				}
			}

			if(tok.value.substr(1)!="dim" && tok.value.substr(1)!="bright"&& tok.value.substr(1)!="underline"){
				if(tok.value[0] == '/'){
					st.pop();
						if(!st.empty()){
							tagValue = st.top();
						}
						else{
							tagValue = "";
						}
				}
			}	
			else{
				if(tok.value[0] == '/'){
					st_att.pop();
					Ident += term_attrib();
						if(!st_att.empty()){
							attribValue = st_att.top();
						}
						else{
							attribValue ="";
						}
				}	
				else{
					if(!st_att.empty()){
						attribValue = st_att.top();
					}
					else{
						attribValue="";
					}
				}
			}
			if(tok.type == IDENT || tok.type == BLANK){
				Ident = Ident + tok.value;
			}
			Return +=term_fg()+ term_attrib(displayMapAttr[attribValue])+term_fg(displayMap[tagValue])+Ident+term_fg();
			Ident = "";	
		}
	return Return;
	}
return displayString;
}

/**
 * -----------------------------------------------------------------------------
 * 
 *  check whether the given expression is well-formed
 *  - if it is NOT well-formed, return one of the three error messages:
 *     "INVALID TOKEN"
 *     "EXPRESSION NOT WELL-FORMED"
 *     "UNKNOWN TAG"
 *  - if it is well-formed, return "VALID"
 * -----------------------------------------------------------------------------
 */
string validate(const string& expression)
{

stack<string> st;

Token tok;
Lexer lex;
lex.set_input(expression);
	
	while(lex.has_more_token()){
		tok = lex.next_token();	
		if(tok.type == TAG && tok.value[0]!='/'){
			st.push(tok.value);
		}
		if(tok.value[0] == '/'){
			if(!st.empty()){
				if(tok.value.substr(1)==st.top()){
					st.pop();
				}
				
				else if(tok.value.substr(1)!=st.top()){
					return"EXPRESSION NOT WELL FORMED";
				}						
			}
			else{
				return "EXPRESSION NOT WELL FORMED";
			}	    
		}
		if(tok.type == ERRTOK){
			return "INVALID TOKEN";
		}
	}	
	if(st.empty()){
		return "VALID";
	}
	return "UNKNOWN TAG";
}

