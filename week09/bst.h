/***********************************************************************
 * Component:
 *    Week 09, Binary Search Tree (BST)
 *    Brother Helfrich, CS 235
 * Author:
 *    Justin Waite & Winson So
 * Summary:
 *    This file contains the class definitions for a Binary Search Tree
 *    and its iterator. A Binary Search Tree is an ordered binary tree
 *    which makes it trivial to search.
 ************************************************************************/

#ifndef BST_H
#define BST_H

#include "bnode.h"
#include "stack.h"

// stub definition for BSTIterator
template <class T>
class BSTIterator;

/*******************************************
 * CLASS BST
 * A binary sort tree is an order binary tree
 * which allows for simple searching since
 * an order is kept.
 ******************************************/
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
   void insert(const T & data) throw (const char *);

   // auxiliary recursive function used for insert.
   void insertAux(BinaryNode<T> * subRoot, const T & data) throw (const char *);

   // deletes all the elements in the binary tree.
   void clear() { deleteBinaryTree(pRoot); }

   // removes an item at the given iterator.
   void remove(BSTIterator<T> & it);

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

/*******************************************
 * CLASS BSTIterator
 * An iterator for the BST class. Nasty little
 * devil.
 ******************************************/
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

/*******************************************
 * BSTIterator NON-DEFAULT CONSTRUCTOR
 * Constructor that takes a bnode pointer
 ******************************************/
template <class T>
inline BSTIterator<T> :: BSTIterator(const BinaryNode<T> * p)
{
   nodes.push(0);
   nodes.push(p);
}

/*******************************************
 * BST COPY CONSTRUCTOR
 * Copy constructor for the BST class.
 ******************************************/
template <class T>
inline BST<T> :: BST(const BST<T> & rhs)
{
   pRoot = rhs.pRoot;
}

/*******************************************
 * BST INSERT
 * Calls the insertAux function to INSERT
 * the data into the binary tree recursively.
 ******************************************/
template <class T>
void BST<T> :: insert(const T & data) throw (const char *)
{
   insertAux(pRoot, data);
}

/*******************************************
 * BST INSERT AUX
 * Traverses the tree to find where to insert
 * the data. Inserts the data in that spot.
 ******************************************/
template <class T>
void BST<T> :: insertAux(BinaryNode<T> * subRoot, const T & data) throw (const char *)
{
   if (subRoot == 0)
   {
      try
      {
         subRoot = new BinaryNode<T>(data);
      }
      catch(std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a node";
      }
   }
   else if (data < subRoot->data)
      insertAux(subRoot->pLeft, data);
   else if (data > subRoot->data)
      insertAux(subRoot->pRight, data);
}

/**************************************************
 * BST ITERATOR :: DECREMENT PREFIX
 *     advance by one. Note that this implementation uses
 *     a stack of nodes to remember where we are. This stack
 *     is called "nodes".
 * Author:      Br. Helfrich
 * Performance: O(log n) though O(1) in the common case
 *************************************************/
template <class T>
BSTIterator <T> & BSTIterator <T> :: operator -- ()
{
   // do nothing if we have nothing
   if (nodes.top() == NULL)
      return *this;

   // if there is a left node, take it
   if (nodes.top()->pLeft != NULL)
   {
      nodes.push(nodes.top()->pLeft);

      // there might be more right-most children
      while (nodes.top()->pRight)
         nodes.push(nodes.top()->pRight);
      return *this;
   }

   // there are no left children, the right are done
   assert(nodes.top()->pLeft == NULL);
   BinaryNode <T> * pSave = nodes.top();
   nodes.pop();

   // if the parent is the NULL, we are done!
   if (NULL == nodes.top())
      return *this;

   // if we are the right-child, go to the parent.
   if (pSave == nodes.top()->pRight)
      return *this;

   // we are the left-child, go up as long as we are the left child!
   while (nodes.top() != NULL && pSave == nodes.top()->pLeft)
   {
      pSave = nodes.top();
      nodes.pop();
   }

   return *this;
}

#endif // BST_H
