#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <stdexcept>

#include "UBHeap.h"
#include "error_handling.h"
#include "term_control.h"

using namespace std;

void prompt();
typedef void (*cmd_t)(istringstream&);
void bye(istringstream&);
void print_cmd(istringstream&);
void new_cmd(istringstream&);
void top_cmd(istringstream&);
void pop_cmd(istringstream&);
void push_cmd(istringstream&);

map<string,UBHeap> heap_table;

const string usage_msg = "UBHeap: Amey's Heap implementation";

int main()
{
	map<string,cmd_t> cmd_map;
	cmd_map["exit"] = &bye;
	cmd_map["bye"] = &bye;
	cmd_map["quit"] = &bye;
	cmd_map["new"] = &new_cmd;
	cmd_map["print"]= &print_cmd;
	cmd_map["top"] = &top_cmd;
	cmd_map["push"]=&push_cmd;
	cmd_map["pop"] = &pop_cmd;

	cout<<term_cc(YELLOW)<<usage_msg<<endl;

	istringstream iss;
	string cmd;
	string line;
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


void bye(istringstream& iss){
	exit(0);
}

void new_cmd(istringstream& iss){
	string heap_name;
	char a;
	int member;
	if(!(iss>>heap_name)||!(iss>>a)||a!= '='){
		throw runtime_error("Syntax: new heapname = [list of integers]");
	}
	vector<int> int_list;
	while(iss>>member)
		int_list.push_back(member);

	UBHeap ubheap;
	ubheap = UBHeap(int_list);
	heap_table[heap_name] = ubheap;
}

void print_cmd(istringstream& iss){
	string heap_name, tmp;
    if (!(iss >> heap_name) || (iss >> tmp))
        throw runtime_error("Syntax: print heapName");
    if (heap_table.find(heap_name) == heap_table.end())
        throw runtime_error(string("Heapname ") + heap_name + " not found");
    cout << term_cc(YELLOW) << heap_table[heap_name].toString()
         << endl << term_cc();
}

void top_cmd(istringstream& iss){
	string name, tmp;
	if(!(iss>>name) || (iss>>tmp))
		throw runtime_error("Syntax: top [heapname]");
	if(heap_table.find(name) == heap_table.end())
		throw runtime_error(string("Heap ")+name+" not found");
	if(heap_table[name].empty())
		throw runtime_error("Heap is Empty");
 
	 cout<< term_cc(YELLOW)<<heap_table[name].top()
	     <<endl << term_cc();
}

void pop_cmd(istringstream& iss){
	string name,tmp;
	if(!(iss>>name) || (iss>>tmp))
		throw runtime_error("Syntax: pop [heapname]");
	if(heap_table.find(name) == heap_table.end())
		throw runtime_error(string("Heap ")+name+" not found");
	if(heap_table[name].empty())
		throw runtime_error("Heap is Empty");
	
	heap_table[name].pop();
}

void push_cmd(istringstream& iss){
	int number;
	string name,tmp;
	if(!(iss>>name) || !(iss>>number) || (iss>>tmp))
		throw runtime_error("Syntax: push [heapname] [number]");
	if(heap_table.find(name) == heap_table.end())
		throw runtime_error(string("Heapname ") + name + " not found");
	heap_table[name].push(number);	
}

void prompt(){
	
	cout <<term_cc(BLUE)<<"> "<<term_cc()<<flush;
}
