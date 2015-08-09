// ============================================================================ 
// UBHeap.h
// ~~~~~~~~
// Amey Mahajan
// - a simple Max Heap class
// ============================================================================ 


#ifndef UBHeap_H_
#define UBHeap_H_
#include <vector>

class UBHeap
{

public:

	/**
     * construct a heap from a given array
     * since this has a default parameter, there's a lurking default
     * constructor in here too
     */
	explicit UBHeap(const std::vector<int> &a = std::vector<int>());
	UBHeap& operator=(const UBHeap& theOther);

	std::string toString();
	void push(int);
	void pop();
	int top();
	bool empty();

private:
	std::vector<int> heap_;
	void heapify();
	void sink(size_t i);
	void floatUp(size_t i);	
};


#endif
