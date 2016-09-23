// File:        redblacktree.h
// Date:        2016-02-27
// Description: Declaration of a RedBlackTree class and template Node class 

#ifndef _REDBLACKTREE_H_
#define _REDBLACKTREE_H_

#include <cstdlib>
#include <stdexcept>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

template <class T>
class Node {
public:
    T data;
    Node<T>* left;
    Node<T>* right;
    Node<T>* p; // parent pointer
    bool is_black;

    // parameterized constructor

    Node(T value) {
        data = value;
        left = NULL;
        right = NULL;
        p = NULL;
        is_black = false;
    }
};

template <class T>
class RedBlackTree {
private:

    Node<T>* root;
    int size;

    // recursive helper function for deep copy
    // creates a new node based on sourcenode's contents, links back to parentnode,
    //   and recurses to create left and right children
    Node<T>* CopyTree(Node<T>* thisnode, Node<T>* sourcenode, Node<T>* parentnode);

    // recursive helper function for tree deletion
    // deallocates nodes in post-order
    void RemoveAll(Node<T>* node);

    // performs BST insertion and returns pointer to inserted node
    // Note that this should only be called if item does not already exist in the tree
    // Does not increase tree size.
    Node<T>* BSTInsert(T item); //Done

    // helper function for in-order traversal
    void InOrder(const Node<T>* node, T* arr, int arrsize, int& index) const; //Done

    // rotation functions
    void LeftRotate(Node<T>* node); //Done
    void RightRotate(Node<T>* node); //Done

    // get the predecessor of a node
    Node<T>* Predecessor(Node<T>* node); //Done

    // Tree fix, performed after removal of a black node
    // Note that the parameter x may be NULL
    void RBDeleteFixUp(Node<T>* x, Node<T>* xparent, bool xisleftchild);

    // Calculates the height of the tree
    // Requires a traversal of the tree, O(n)
    unsigned int CalculateHeight(Node<T>* node) const;

public:

    // default constructor--------------------------------------------------
    RedBlackTree();

    // copy constructor, performs deep copy of parameter
    RedBlackTree(const RedBlackTree<T>& rbtree);

    // destructor
    // Must deallocate memory associated with all nodes in tree
    ~RedBlackTree();

    // Mutator functions-----------------------------------------------------

    // Calls BSTInsert and then performs any necessary tree fixing.
    // If item already exists, do not insert and return false.
    // Otherwise, insert, increment size, and return true.
    bool Insert(T item);

    // Removal of an item from the tree.
    // Must deallocate deleted node after RBDeleteFixUp returns
    bool Remove(T item);

    // deletes all nodes in the tree. Calls recursive helper function.
    void RemoveAll();

    // Accessor functions------------------------------------------------------

    // Returns existence of item in the tree.
    // Return true if found, false otherwise.
    bool Search(T item) const; //Done

    // Searches for item and returns a pointer to the node contents so the
    //   value may be accessed or modified
    // Use with caution! Do not modify the item's key value such that the
    //   red-black / BST properties are violated.
    T* Retrieve(T item); //Done

    // performs an in-order traversal of the tree
    // arrsize is the size of the returned array (equal to tree size attribute)
    T* Dump(int& arrsize) const; //Done

    // returns the number of items in the tree
    unsigned int Size() const;

    // returns the height of the tree, from root to deepest null child. Calls recursive helper function.
    // Note that an empty tree should have a height of 0, and a tree with only one node will have a height of 1.
    unsigned int Height() const;

    // returns a pointer to the root of the tree
    // NOTE: This will be used only for grading.
    // Providing access to the tree internals is dangerous in practice!

    Node<T>* GetRoot() const {
        return this->root;
    }

    // overloaded assignment operator
    RedBlackTree<T>& operator=(const RedBlackTree<T>& rbtree);
};

#include "rbtreepartial.cpp"
#include "redblacktree.cpp"

#endif