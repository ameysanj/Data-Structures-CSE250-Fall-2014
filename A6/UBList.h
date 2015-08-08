// ============================================================================ 
// UBList.h
// ~~~~~~~~
// hqn
// - a simple singly linked list class
// - DO NOT MODIFY THIS FILE
// ============================================================================ 

#ifndef UBList_H_
#define UBList_H_

class UBList
{
private:
    // Node is a private structure of UBList, users don't need to know about it
    struct Node 
    {
        int   key;
        Node* next;
        Node(int k=0, Node* n=NULL) : key(k), next(n) {};
    };

    Node* head;
    size_t numNodes;

public:
    UBList(Node* h=NULL, size_t n=0);          // default constructor
    UBList(const UBList& theOther);            // copy constructor
    UBList& operator=(const UBList& theOther); // assignment operator
    ~UBList();                                 // destructor

    void swap(UBList& theOther); // swap two lists
    std::string toString();      // print all members of the list
    void insert(int);            // insert a new int to the head of the list
    bool isSorted();             // verify whether the current list is sorted

    void remove(int);             // remove all nodes with given key
    void merge(UBList& theOther); // merge with theOther
    void sort();                  // merge sort
};

#endif
