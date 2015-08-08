#include <iostream>
#include "../term_control.h"

using namespace std;

int main()
{
    cout << term_fg(CYAN) 
        << "This is cyan "
        << term_attrib(UNDERLINE)
        << "this is underlined"
        << term_attrib(DIM)
        << " and dim "
        << term_attrib()
        << term_attrib(UNDERLINE)
        << term_fg(CYAN)
        << "and underlined"
        << term_cc()
        << endl;
    return 0;
}
