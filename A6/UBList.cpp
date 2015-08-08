
// ============================================================================ 
// UBList.cpp
// ~~~~~~~~~~
// @author Amey S. Mahajan 
// - implement the UBList interface
// ============================================================================ 

#include <cstddef> // this header defines NULL
#include <iostream>
#include <stdexcept>
#include <sstream>

#include "UBList.h"

using namespace std; // BAD PRACTICE

// ============================================================================ 
// DO NOT MODIFY THIS SECTION
// ============================================================================ 
UBList::UBList(Node* h, size_t n) : head(h), numNodes(n)
{
}

UBList::UBList(const UBList& theOther)
{
    Node* cur;
    head = NULL;
    numNodes = 0;
    Node* ptr = theOther.head;
    while (ptr != NULL) {
        numNodes++;
        if (head == NULL) {
            cur = head = new Node(ptr->key);
        } else {
            cur->next = new Node(ptr->key);
            cur = cur->next;
        }
        ptr = ptr->next;
    }
}

void UBList::swap(UBList& theOther)
{
    std::swap(numNodes, theOther.numNodes);
    std::swap(head, theOther.head);
}

UBList& UBList::operator=(const UBList& theOther)
{
    UBList temp(theOther); // deep copy
    swap(temp);
    return *this;
}

UBList::~UBList() 
{
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

void UBList::insert(int x)
{
    head = new Node(x, head);
    numNodes++;
}

string UBList::toString()
{
    ostringstream oss;
    oss << "[" << numNodes << " NODES] : ";
    Node* ptr = head;
    while (ptr != NULL) {                                                       
        oss << ptr->key << " ";                                                
        ptr = ptr->next;                                                        
    }                                                                           
    return oss.str();
}

bool UBList::isSorted()
{
    for (Node* ptr = head; ptr != NULL && ptr->next != NULL; ptr = ptr->next)
        if (ptr->key > ptr->next->key) 
            return false;
    return true;
}

// ============================================================================ 
// Merge function 
// 
// ============================================================================ 
void UBList::merge(UBList& theOther)
{
    if (!this->isSorted() || !theOther.isSorted())
        throw runtime_error("Give give me sorted lists to merge");
	

    // TODO: your code goes here
    // + this function merges the current list with the list pointed to by
    // theOther.head
    // + we assume that both lists are already sorted
    // + by manipulating pointers, eventually head points to a sorted (merged)
    // list, and you have to set theOther.head = NULL and theOther.numNodes = 0
    // after all is done.
    // + update numNodes accordingly too

Node* t1 = head;
Node* t2 = theOther.head;
Node* t3 = NULL;
	if(theOther.head ->key <= head->key){
		t3 = theOther.head;		
		t2 = t2->next;
		head = theOther.head;	
		theOther.head = t2;
	}
	else{
		t3 = head;
		t1=t1->next;
		theOther.head = head;
	}
	while(t1!= NULL && t2!=NULL){
		if(t2->key < t1->key){
			t3->next = t2;
			t3 = t2;
			t2= t2->next;
		}
		else if(t1->key<=t2->key){
			t3->next = t1;
			t3 = t1;
			t1 = t1->next;
		}
	}
	if(t1 == NULL){
		t3->next = t2;
	}
	if(t2 == NULL){
		t3->next = t1;	
	}
	else{
		numNodes = numNodes + theOther.numNodes;
		theOther.head = NULL;
		theOther.numNodes = 0;
	}
}

void UBList::remove(int x)
{
    // TODO: your code goes here
    // + remove all nodes whose key = x.
    // + remember to delete (pointers to) those nodes
Node* temp = head;
	while(temp->next != NULL){
		if(temp->next->key != x){
			temp = temp->next;
		}
		else{
			Node* temp2 = temp->next;
			temp->next = temp2->next;
			delete temp2;
			numNodes--;
		}
		if(head->key == x){
			Node* temp3 = head;
			head = head->next;
			delete temp3;	
			numNodes--;
		}
			

		if(head->next == NULL){
			if(head->key == x){
				cout<<"HERE"<<endl;
				head = NULL;
				delete head;
				numNodes--;
			}
		}
	}
	if(head->next == NULL){
		if(head->key == x){
			cout << "I am here too"<<endl;
			head = NULL;
			delete head;
			numNodes--;
		}
	}
}

void UBList::sort()
{
    // TODO: your code goes here
    // + merge sort algorithm
    // + only pointer manipulation is allowed
    // + use merge() as a subroutine
	Node* c = head;
	int counter = 1 ;
	Node* secondStart = NULL;
		if(c!=NULL ||c->next != NULL){
			while(counter < numNodes-numNodes/2){
				c = c->next;
				counter++;
			}	
			if(counter == numNodes-numNodes/2){
				secondStart = c->next;
				c->next = NULL;	
					cout<<counter<<endl;
					UBList first(head, counter);
					UBList second(secondStart, numNodes-counter);
					first.sort();
					second.sort();
				first.merge(second);
				swap(first);
			}
			cout<<"I AM NULL"<<endl;	
		}
		return;
}

/**
New Changes begin here.
**/

void UBList::swapKey(UBList &theOther){
	Node* ptr = head;
	Node* temp = head;
	int i = 1;

		if(ptr == NULL){
			return;
		}
		else{
			while(i<numNodes-numNodes/2){			
				ptr = ptr->next;
			}	
			
		}
}

void UBList::duplicate(UBList &theOther){

	Node* temp = head;
	Node* ptr = head->next;
	
	while(temp!=NULL && ptr!=NULL){
		if(temp->key == ptr->key){
			temp->next = ptr->next;
			delete ptr;
		}
		else{
			temp= temp->next;
			ptr = ptr->next;
		}
	}
}



