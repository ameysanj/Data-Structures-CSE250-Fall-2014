// ============================================================================
// term_control.cpp
// ~~~~~~~~~~~~~~~~
// author: hqn
// may 04, 2014
// - a few terminal control routines for pretty output printing
// ============================================================================

#include <sstream>
#include <inttypes.h>
#include "term_control.h"

std::string term_cc(term_colors_t fg, term_colors_t bg, term_attrib_t attr) 
{
    std::ostringstream oss;
    oss << uint8_t(0x1b) << '[' << char(attr) << ";3" << char(fg) 
        << ";4" << char(bg) << 'm';
    return oss.str();
}

std::string term_clear() 
{
    std::ostringstream oss;
    oss << uint8_t(0x1b) << "[2J";
    return oss.str();
}
