
/**==================================================
 *UBHeap.cpp
 ~~~~~~~~~~~~
 * Amey Mahajan
**/

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <sstream>

#include "UBHeap.h"

using namespace std;


UBHeap::UBHeap(const std::vector<int> &a) : heap_(a)
{
	heapify();
}

UBHeap& UBHeap::operator=(const UBHeap& theOther){
	heap_ = theOther.heap_;
	return *this;
}
string UBHeap::toString(){
	ostringstream oss; 
	for(size_t index = 0; index<heap_.size();index++){
		oss<<heap_[index]<<" ";
	}
	return oss.str();
}

int UBHeap::top(){
	return heap_[0];
}

void UBHeap::push(int a){
	heap_.push_back(a);
		floatUp(heap_.size()-1);
}

void UBHeap::pop(){
	swap(heap_[0],heap_[heap_.size()-1]);
	heap_.pop_back();
	sink(0);
}
bool UBHeap::empty(){
	return heap_.size()==0;
}
void UBHeap::heapify(){
	for(int i = heap_.size()/2;i>=0;i--){
		sink(i);
	}
}

void UBHeap::sink(size_t x){
	size_t left = 2*x+1;
	if(left>=heap_.size()){
		 return;
	}
	size_t right = left+1;
	size_t my_pick;
	if(right>= heap_.size()){
		my_pick = left;
	}
	else if(heap_[right]>heap_[left]){
		my_pick = right;
	}
	else{
		my_pick =left;
	}
	if(heap_[x] < heap_[my_pick]){
		swap(heap_[x],heap_[my_pick]);
		sink(my_pick);
	}
}

void UBHeap::floatUp(size_t index){
	size_t parent = (index-1)/2;
	if(index == 0){
		return;
	}
	else if(heap_[index]>heap_[parent]){
		swap(heap_[parent],heap_[index]);
		floatUp(parent);
	}
}






