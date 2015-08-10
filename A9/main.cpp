// ============================================================================
// main.cpp
// ~~~~~~~~
// hqn
// - driver program to test SplayTree's implementation
// - the program handles the following commands
// - exit
// - newtree (clears old tree, start afresh)
// - print (prints the current tree)
// - insert key (insert a new key in the tree)
// - remove key (remove a key, if any, from the current tree)
// - find key (find a key)
// ============================================================================

#include <iostream>
#include <stdexcept>
#include <iterator>
#include <map>
#include <sstream>
#include <vector>
#include <cstdlib>   // for exit()

#include "SplayTree.h"
#include "term_control.h"
#include "error_handling.h"

using namespace std; // BAD PRACTICE

typedef void (*cmd_t)(istringstream&);

// -----------------------------------------------------------------------------
// prototypes of some other functions used in this driver
// -----------------------------------------------------------------------------
void prompt() { cout << term_cc(BLUE) << "> " << term_cc() << flush; }

void new_tree(istringstream&); // returns a new tree
void print(istringstream&);    // print the current tree
void insert(istringstream&);   // print the current tree in postorder
void remove(istringstream&);   // print the current tree in inorder
void find(istringstream&);     // print the current tree in levelorder

void bye(istringstream& tmp) { exit(0); } // simply quit

// global variable, new_tree() changes this variable
SplayTree tree;   

int main() 
{
    const string usage_msg = "UB Splay Tree Driver. Version 0.7\n"
                             " hqn\n"
                             " Please report bugs to hungngo@buffalo.edu\n";

    cout << term_cc(YELLOW) << usage_msg << endl;

    map<string,cmd_t> cmd_map;
    cmd_map["newtree"]    = &new_tree;
    cmd_map["nt"]         = &new_tree;
    cmd_map["exit"]       = &bye;
    cmd_map["bye"]        = &bye;
    cmd_map["quit"]       = &bye;
    cmd_map["print"]      = &print;
    cmd_map["insert"]     = &insert;
    cmd_map["remove"]     = &remove;
    cmd_map["find"]       = &find;

    string cmd, line;
    istringstream iss;
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
            error_return(string("Unknown command ") + cmd);
        }
    }
    return 0;
}

void new_tree(istringstream& iss) 
{
    string tmp;
    if (iss >> tmp)
        throw runtime_error("Usage: newtree");
    tree.clear();
}

void print(istringstream& iss) 
{
    string tmp;
    if (iss >> tmp)
        throw runtime_error("Usage: print");
    cout << term_cc(CYAN) << tree.toString() << term_cc();
}

void insert(istringstream& iss) 
{
    string tmp;
    int key;
    while (iss >> key) {
        if (!tree.insert(key))
            cout << term_cc(RED) << key << " inserted before" << endl;
        else
            cout << term_cc(YELLOW) << key << " just inserted" 
                << endl << term_cc();
    }
}

void remove(istringstream& iss) 
{
    string tmp;
    int key;
    if (!(iss >> key) || (iss >> tmp))
        throw runtime_error("Usage: remove key");
    if (!tree.remove(key)) {
        ostringstream tmp;
        tmp << "Key " << key << " NOT removed" << endl;
        throw runtime_error(tmp.str());
    } else {
        cout << term_cc(YELLOW) << key << " removed!" 
             << endl << term_cc();
    }
}

void find(istringstream& iss) 
{
    string tmp;
    int key;
    if (!(iss >> key) || (iss >> tmp))
        throw runtime_error("Usage: find key");
    if (tree.findKey(key))
        cout << term_cc(YELLOW) << key << " FOUND" << endl << term_cc();
    else
        cout << term_cc(YELLOW) << key << " NOT FOUND" << endl << term_cc();
}
