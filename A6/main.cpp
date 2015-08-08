// ============================================================================ 
// main.cpp
// ~~~~~~~~
// author: hqn
// Description: get a user's command of the form
// - new listname = [list of non-negative integers separated by space]
// - print listname
// - remove element
// - sort listname
// - merge listname1 listname2
// - exit
// their meanings are described in the assignment 6 specification
// ============================================================================ 
#include <cstdlib>   // for exit(0)
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <stdexcept>

#include "UBList.h"
#include "error_handling.h"
#include "term_control.h"

using namespace std; // BAD PRACTICE

void prompt();
typedef void (*cmd_t)(istringstream&);
void bye(istringstream&);
void new_cmd(istringstream&);
void print_cmd(istringstream&);
void sort_cmd(istringstream&);
void remove_cmd(istringstream&);
void merge_cmd(istringstream&);

map<string, UBList> list_table; // our "symbol table"

const string usage_msg = "UBList: practice manipulating linked lists";

int main() 
{
    map<string,cmd_t> cmd_map;
    cmd_map["exit"]   = &bye;
    cmd_map["bye"]    = &bye;
    cmd_map["quit"]   = &bye;
    cmd_map["new"]    = &new_cmd;
    cmd_map["print"]  = &print_cmd;
    cmd_map["sort"]   = &sort_cmd;
    cmd_map["remove"] = &remove_cmd;
    cmd_map["rm"]     = &remove_cmd;
    cmd_map["merge"]  = &merge_cmd;
	
	//new Work from here
	cmd_map["duplicate"] = &duplicate_cmd;
	//till here 
    cout << term_cc(YELLOW) << usage_msg << endl;

    istringstream iss;
    string cmd, line;
    while (cin) {
        prompt(); 
        getline(cin, line);
        iss.clear();
        iss.str(line);
        if (!(iss >> cmd))
            continue;

        if (cmd_map.find(cmd) != cmd_map.end()) {
            try {
                cmd_map[cmd](iss);
            } catch (runtime_error &e) {
                error_return(e.what());
            }
        } else {
            error_return("Unknown command");
        }
    }
    return 0;
}

void bye(istringstream& iss)
{
    exit(0);
}

void new_cmd(istringstream& iss)
{
    string list_name;
    char a;
    int member;
    if (!(iss >> list_name) || !(iss >> a) || a != '=') {
        throw runtime_error("Syntax: new listName = [list of ints]");
    }
    vector<int> int_list;
    while (iss >> member)             // sloppy with error checking here
        int_list.push_back(member);

    UBList ublist;
    for (size_t i=int_list.size(); i>0; --i)
        ublist.insert(int_list[i-1]);

    list_table[list_name] = ublist; // assignment operator called!
}

void print_cmd(istringstream& iss)
{
    string list_name, tmp;
    if (!(iss >> list_name) || (iss >> tmp))
        throw runtime_error("Syntax: print listName");
    if (list_table.find(list_name) == list_table.end())
        throw runtime_error(string("Listname ") + list_name + " not found");
    cout << term_cc(YELLOW) << list_table[list_name].toString() 
         << endl << term_cc();
}

void sort_cmd(istringstream& iss)
{
    string name, tmp;
    if (!(iss >> name) || (iss >> tmp))
        throw runtime_error("Syntax: sort [listname]");
    if (list_table.find(name) == list_table.end())
        throw runtime_error(string("List ") + name + " not found");
    list_table[name].sort();
}

void remove_cmd(istringstream& iss)
{
    int element;
    string name, tmp;
    if (!(iss >> name) || !(iss >> element) || (iss >> tmp))
        throw runtime_error("Syntax: remove [somelist] [someint]");
    if (list_table.find(name) == list_table.end())
        throw runtime_error(string("Listname ") + name + " not found");
    list_table[name].remove(element);
}

void merge_cmd(istringstream& iss)
{
    string name1, name2, tmp;
    if (!(iss >> name1) || !(iss >> name2) || (iss >> tmp))
        throw runtime_error("Syntax: merge list1 list2");
    if (list_table.find(name1) == list_table.end())
        throw runtime_error(string("List ") + name1 + " not found");
    if (list_table.find(name2) == list_table.end())
        throw runtime_error(string("List ") + name2 + " not found");
    list_table[name1].merge(list_table[name2]);
}

void prompt() 
{
    cout << term_cc(BLUE) << "> " << term_cc() << flush;
}
