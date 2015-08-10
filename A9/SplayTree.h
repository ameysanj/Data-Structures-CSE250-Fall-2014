// ============================================================================
// SplayTree.h
// ~~~~~~~~~~~~
// hqn
// - A Very Basic Splay Tree Class
// - Nodes have int payloads
// - To make it "useable", we need to make it a template class, with arbitrary
//   (Key, Value) as in the sample AVL code posted on the lecture notes
// - Then we also need an assignment operator, copy constructor, etc.
//
// - Here I'm simpifying things to the fullest so you can concentrate on the
//   a few operations you are supposed to implement
// ============================================================================

#ifndef SPLAY_TREE_H_
#define SPLAY_TREE_H_

#include <vector>
#include <string>
#include <map>

class SplayTree
{
private:
    struct Node 
    {
        int key;
        Node* left;
        Node* right;
        Node* parent;
        Node(int k = 0, Node* l = NULL, Node* r = NULL, Node* p = NULL) 
            : key(k), left(l), right(r), parent(p)
        {}
        std::string toString();
    };

public:
    // default constructor
    SplayTree() : root_(NULL) 
    { }

    // destructor
    ~SplayTree();

    // clear the tree, deallocate space
    void clear();

    // simple size check
    bool isEmpty() const;

    // print the tree symmetrically
    std::string toString();

    // insert a new key in the tree, return 
    //  - true if a new node was created (and inserted)
    //  - false if the key already exists
    bool insert(int key);

    // remove a key from the tree, return 
    //  - true if a node was removed
    //  - false if the key is not found
    bool remove(int key);

    // returns whether a key is in the tree
    bool findKey(int key);

private:
    // root of the tree
    Node* root_;

    // helper function for destructor and clear()
    void clearTree(Node*);

    // the following four are often necessary in BST operations
    Node* minimum(Node* node); // minimum under node's subtree
    Node* maximum(Node*);      // maximum under node's subtree
    Node* successor(Node*);
    Node* predecessor(Node*);

    // look for a node with a given key, return NULL if not found
    // if not found, splay the node just before hitting NULL
    // if found, DON'T splay, let the caller do it
    Node* findNode(int key); 

    // helper functions for SplayTree operations
    void splay(Node*);
    void leftRotate(Node*&);  // note that the pointer is passed by reference
    void rightRotate(Node*&); // note that the pointer is passed by reference

    /**
     * ** helper functions, data types, and data for symmetric print **
     * ------------------------------------------------------------------------
     *  computeCoordinates() computes both the width and the "midpoint" of the 
     *  box enclosing each subtree rooted at 'root'
     *  Base cases:
     *  - the width is 1 if the node is NULL, offset = 1
     *  - if both the left and the right children are NULL, then
     *    width = payload.length()
     *    offset = (payload.length()+1)/2
     *
     *  Inductive cases:
     *
     *  Case 1: payload + 2 + lo + r-ro + 1 <= l+r+1
     *
     *  ----------
     *            \
     *        __payload___
     *       /            \  <--- these are called "connectives"
     *  ----------    ----------
     *  | left   |    | right  |
     *  | width  |    | width  |
     *  ----------    ----------
     *  =====1     1  ======----     
     *   lo           ro    r-ro
     *
     *  the width is l+r+1
     *  new offset is lo + (l+r+1-(r-ro+1)-lo)/2 + 1
     *              = lo + (l+ro-lo)/2 + 1
     *
     *  Case 2: payload + lo + r-ro + 1 >= l+r
     *
     *  ----------
     *            \
     *        payloadlong
     *       /           \  <--- these are called "connectives"
     *  ----------   ----------
     *  | left   |   | right  |
     *  | width  |   | width  |
     *  ----------   ----------
     *  =====1    x  ======----     
     *   lo          ro    r-ro
     *
     *  here, we want l+r+x = payload + 2 + lo + r - ro + 1
     *  and hence x = payload+lo-ro+3-l
     *
     *  new offset is lo + (l+r+x-(r-ro+1)-lo)/2 + 1
     *              = lo + (l+ro-lo+x-1)/2 + 1
     *
     *  In both cases,
     *  x = max(payload+lo+r-ro+2,l+r) -l-r+1
     *  the width is l + x + r.
     *  and new offset is lo + (l+ro-lo+x-1)/2 + 1
     * ------------------------------------------------------------------------
     */
    struct Text 
    {
        std::string text; // the text to be printed, e. "abc__"
        size_t pos;       // its position on the line
        Text(std::string t="", size_t p=0) : text(t), pos(p) {}
    };

    struct Coordinate 
    {
        size_t width;  // width of a subtree box
        size_t offset; // offset to where the parent points
    };

    std::string printLevel(const std::vector<Text>&);
    void computeCoordinates(Node*);
    std::map<Node*, Coordinate> coordinate_;
};

#endif
