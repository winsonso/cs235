/***********************************************************************
 * Component:
 *    Week 09, Binary Search Tree (BST)
 *    Brother Helfrich, CS 235
 * Author:
 *    Justin Waite & Winson So
 * Summary:
 *
 ************************************************************************/

#ifndef BST_H
#define BST_H

#include "bnode.h"
#include "stack.h"

// stub class for BSTIterator
template <class T>
class BSTIterator;

template <class T>
class BST
{
public:
   // default constructor
   BST() : pRoot(0) {}

   // copy constructor
   BST(const BST & rhs);

   // destructor
   ~BST() { deleteBinaryTree(pRoot); }

   // assignment operator
   BST & operator = (const BST & rhs);

   // checks to see if the tree is empty.
   bool empty() const { return pRoot = 0; }

   // inserts an item into the tree in the proper spot.
   void insert(T & data) throw (const char *);

   // removes an item at the given iterator.
   // void remove(BSTIterator & it);

   // deletes all the elements in the binary tree.
   void clear() { deleteBinaryTree(pRoot); }

   // finds an element in the binary tree.
   BSTIterator<T> & find(T t);

   // an iterator referring to the leftmost element in the BST.
   BSTIterator<T> & begin();

   // an null iterator
   BSTIterator<T> & end();

   // an iterator referring to the rightmost element in the BST.
   BSTIterator<T> & rbegin();

   // an null iterator
   BSTIterator<T> & rend();

private:
   BinaryNode<T> * pRoot;
};

template <class T>
class BSTIterator
{
public:
   // non-default taking a binary node pointer
   BSTIterator(const BinaryNode<T> * p);

   // non-default taking a stack
   BSTIterator(const Stack<BinaryNode<T> *> nodes) : nodes(nodes) {}

   // copy constructor
   BSTIterator(const BSTIterator & rhs) : nodes(rhs.nodes) {}

   // assignment operator
   BSTIterator & operator = (const BSTIterator & rhs);

   // not-equals operator
   bool operator != (const BSTIterator & rhs);

   // dereference operator, const by reference
   const T & operator * (const BSTIterator & rhs);

   // increment postfix operator
   BSTIterator & operator ++ (int postfix);

   // increment prefix operator
   BSTIterator & operator ++ ();

   // decrement postfix operator
   BSTIterator & operator -- (int postfix);

   // decrement prefix operator
   BSTIterator & operator -- ();

private:
   Stack<BinaryNode<T> *> nodes;
};

template <class T>
inline BSTIterator<T> :: BSTIterator(const BinaryNode<T> * p)
{
   nodes.push(0);
   nodes.push(p);
}

/**************************************************
 * BST ITERATOR :: DECREMENT PREFIX
 *     advance by one. Note that this implementation uses
 *     a stack of nodes to remember where we are. This stack
 *     is called "nodes".
 * Author:      Br. Helfrich
 * Performance: O(log n) though O(1) in the common case
 *************************************************/
// template <class T>
// BSTIterator <T> & BSTIterator <T> :: operator -- ()
// {
//    // do nothing if we have nothing
//    if (nodes.top() == NULL)
//       return *this;
//
//    // if there is a left node, take it
//    if (nodes.top()->pLeft != NULL)
//    {
//       nodes.push(nodes.top()->pLeft);
//
//       // there might be more right-most children
//       while (nodes.top()->pRight)
//          nodes.push(nodes.top()->pRight);
//       return *this;
//    }
//
//    // there are no left children, the right are done
//    assert(nodes.top()->pLeft == NULL);
//    BinaryNode <T> * pSave = nodes.top();
//    nodes.pop();
//
//    // if the parent is the NULL, we are done!
//    if (NULL == nodes.top())
//       return *this;
//
//    // if we are the right-child, go to the parent.
//    if (pSave == nodes.top()->pRight)
//       return *this;
//
//    // we are the left-child, go up as long as we are the left child!
//    while (nodes.top() != NULL && pSave == nodes.top()->pLeft)
//    {
//       pSave = nodes.top();
//       nodes.pop();
//    }
//
//    return *this;
// }

#endif // BST_H
