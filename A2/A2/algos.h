// ============================================================================
// algos.h
// ~~~~~~~~~~~~~~~~
// author: hqn 
// - interface to a couple of algorithms
// ============================================================================

#ifndef ALGOS_H_
#define ALGOS_H_

/**
 * takes a filename to a file in SNAP graph format
 * returns the number of distinct edges
 * uses the set-based algorithm
 */
int sba(std::string filename);

/**
 * takes a filename to a file in SNAP graph format
 * returns the number of distinct edges
 * uses the vector-based algorithm
 */
int vba(std::string filename);

#endif // end #ifndef ALGOS_H_
