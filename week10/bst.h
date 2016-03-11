/***********************************************************************
 * Header:
 *    Binary Search Tree (BST)
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
   BST(const BST & rhs) throw (const char *);

   // destructor
   ~BST() { deleteBinaryTree(pRoot); }

   // assignment operator
   BST<T> & operator = (const BST<T> & rhs) throw (const char *);

   // checks to see if the tree is empty.
   bool empty() const { return pRoot == 0; }

   // inserts an item into the tree in the proper spot.
   void insert(const T & data) throw (const char *);

   // deletes all the elements in the binary tree.
   void clear()
   {
      deleteBinaryTree(pRoot);
      this->pRoot = 0;
   }

   // removes an item at the given iterator.
   void remove(BSTIterator<T> & it);

   // finds an element in the binary tree.
   BSTIterator<T> find(const T & t) const;

   // an iterator referring to the leftmost element in the BST.
   BSTIterator<T> begin() const;

   // an null iterator
   BSTIterator<T> end() const { return BSTIterator<T>(0); }

   // an iterator referring to the rightmost element in the BST.
   BSTIterator<T> rbegin() const;

   // an null iterator
   BSTIterator<T> rend() const { return BSTIterator<T>(0); }

private:
   BinaryNode<T> * pRoot;

   // auxiliary recursive function used for insert.
   void insertAux(BinaryNode<T> *& subRoot, const T & data) throw (const char*);

   // auxiliary function used for searching the tree for an item.
   void search(const T & t, bool & found, BinaryNode<T> *& locptr,
               BinaryNode<T> *& parent) const;

   // Private helper method for copying a BST
   BinaryNode<T> *copy(BinaryNode<T> *p) throw (const char *);
};

/*******************************************
 * CLASS BSTIterator
 * An iterator for the BST class.
 ******************************************/
template <class T>
class BSTIterator
{
public:
   // default Constructor, pushed null onto the stack.
   BSTIterator() { nodes.push(0); }

   // non-default taking a binary node pointer
   BSTIterator(BinaryNode<T> * p);

   // non-default taking a stack
   BSTIterator(Stack<BinaryNode<T> *> nodes) : nodes(nodes) {}

   // copy constructor
   BSTIterator(const BSTIterator & rhs) : nodes(rhs.nodes) {}

   // assignment operator
   BSTIterator & operator = (const BSTIterator & rhs);

   // double-equals operator
   bool operator == (const BSTIterator & rhs) const;

   // not-equals operator
   bool operator != (const BSTIterator & rhs) const { return !(*this == rhs); }

   // dereference operator, const by reference
   T & operator * ();

   // increment postfix operator
   BSTIterator operator ++ (int postfix);

   // increment prefix operator
   BSTIterator & operator ++ ();

   // decrement postfix operator
   BSTIterator operator -- (int postfix);

   // decrement prefix operator
   BSTIterator & operator -- ();

private:
   Stack<BinaryNode<T> *> nodes;
};

/*******************************************
 * BST COPY CONSTRUCTOR
 * Copy constructor for the BST class.
 ******************************************/
template <class T>
inline BST<T> :: BST(const BST<T> & rhs) throw (const char *) : pRoot(0)
{
   if (rhs.pRoot == 0)
      return;

   try
   {
      this->pRoot = copy(rhs.pRoot);
   }
   catch (const char * err)
   {
      throw;
   }
}

/*******************************************
 * BST COPY
 * Private helper method for copying a BST
 ******************************************/
template <class T>
BinaryNode<T> * BST<T> :: copy(BinaryNode<T> * pToCopy) throw (const char *)
{
   BinaryNode<T> *pNode;
   try
   {
      pNode = new BinaryNode<T>(pToCopy->data);
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }

   if (pToCopy->pLeft != 0)
      pNode->pLeft = copy(pToCopy->pLeft);
   if (pToCopy->pRight != 0)
      pNode->pRight = copy(pToCopy->pRight);
   return pNode;
}

/*******************************************
 * BST ASSIGNMENT OPERATOR
 * Assignment operator overload for the BST
 * class.
 ******************************************/
template <class T>
BST<T> & BST<T> :: operator = (const BST<T> & rhs) throw (const char *)
{
   if (rhs.pRoot == 0 || this->pRoot != 0)
   {
      this->clear();
      return *this;
   }

   try
   {
      this->pRoot = copy(rhs.pRoot);
   }
   catch (const char * err)
   {
      throw;
   }

   return *this;
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
void BST<T> :: insertAux(BinaryNode<T> *& subRoot, const T & data)
throw (const char *)
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
   else if (data > subRoot->data)
      insertAux(subRoot->pRight, data);
   else // <= allows for duplicates.
      insertAux(subRoot->pLeft, data);
}

/*******************************************
 * BST REMOVE
 * Removes a node at the given iterator
 ******************************************/
template <class T>
void BST<T> :: remove(BSTIterator<T> & it)
{
   bool found;
   BinaryNode<T> * locptr, * parent;
   search(*it, found, locptr, parent);
   if (!found)
      return;

   // If the node has two children
   if (locptr->pLeft != 0 && locptr->pRight != 0)
   {
      //find the inorder successor
      BinaryNode<T> * xSucc = locptr->pRight;
      parent = locptr;
      while (xSucc->pLeft != 0)
      {
         parent = xSucc;
         xSucc = xSucc->pLeft;
      }

      // Move contents of xSucc to x and change x to point to successor.
      // Successor will be removed.
      locptr->data = xSucc->data;
      locptr = xSucc;
   }

   // If the node has 0 or 1 children
   BinaryNode<T> * subtree = locptr->pLeft;
   if (subtree == 0)
      subtree = locptr->pRight;
   if (parent == 0)
      pRoot = subtree;
   else if (parent->pLeft == locptr)
      parent->pLeft = subtree;
   else
      parent->pRight = subtree;
   delete locptr;
}

/*******************************************
 * BST SEARCH
 * A private function used for searching there
 * tree for a given item.
 ******************************************/
template <class T>
void BST<T> :: search(const T & t, bool & found, BinaryNode<T> *& locptr,
                      BinaryNode<T> *& parent) const
{
   locptr = pRoot;
   parent = 0;
   found = false;
   while (!found && locptr != 0)
   {
      if (t < locptr->data)
      {
         parent = locptr;
         locptr = locptr->pLeft;
      }
      else if (locptr->data < t)
      {
         parent = locptr;
         locptr = locptr->pRight;
      }
      else
         found = true;
   }
}

/********************************************
 * BST FIND
 * Using O(log n) to find the item.
 * If the item is greater than the root then
 * go to the right, if not go to the left.
 *******************************************/
template <class T>
BSTIterator<T> BST<T> :: find(const T & t) const
{
   BinaryNode<T> * tmp = pRoot;
   while (tmp != NULL)
   {
      if(tmp->data == t)
         return BSTIterator<T>(tmp);
      if(t > tmp->data)
         tmp = tmp->pRight;
      else
         tmp = tmp->pLeft;
   }
   return BSTIterator<T>(0);
}

/*******************************************
 * BST BEGIN
 * Returns an iterator for the leftmost node.
 ******************************************/
template <class T>
BSTIterator<T> BST<T> :: begin() const
{
   if (pRoot == NULL || pRoot->pLeft == NULL)
      return BSTIterator<T>(pRoot);

   Stack<BinaryNode<T> *> nodes;
   nodes.push(0);
   BinaryNode<T> * pSave = pRoot;
   nodes.push(pRoot);
   while (pSave->pLeft != NULL)
   {
      pSave = pSave->pLeft;
      nodes.push(pSave);
   }

   return BSTIterator<T>(nodes);
}

/*******************************************
 * BST RBEGIN
 * Returns an iterator for the leftmost node.
 ******************************************/
template <class T>
BSTIterator<T> BST<T> :: rbegin() const
{
   if (pRoot == NULL || pRoot->pRight == NULL)
      return BSTIterator<T>(pRoot);

   Stack<BinaryNode<T> *> nodes;
   nodes.push(0);
   BinaryNode<T> * pSave = pRoot;
   nodes.push(pRoot);
   while (pSave->pRight != NULL)
   {
      pSave = pSave->pRight;
      nodes.push(pSave);
   }

   return BSTIterator<T>(nodes);
}

/*******************************************
 * BSTIterator NON-DEFAULT CONSTRUCTOR
 * Constructor that takes a bnode pointer
 ******************************************/
template <class T>
inline BSTIterator<T> :: BSTIterator(BinaryNode<T> * p)
{
   nodes.push(0);
   if (p != 0)
      nodes.push(p);
}

/*******************************************
 * BSTIterator DEREFERENCE OPERATOR
 * Returns the value at the BST
 ******************************************/
template <class T>
T & BSTIterator<T> :: operator * ()
{
   return nodes.top()->data;
}

/*******************************************
 * BSTIterator ASSIGNMENT OPERATOR
 * Returns the value at the BST
 ******************************************/
template <class T>
BSTIterator<T> & BSTIterator<T> :: operator = (const BSTIterator & rhs)
{
   this->nodes = rhs.nodes;
   return *this;
}

/*******************************************
 * BSTIterator COMPARISON OPERATOR
 * Compares the top nodes of two BSTIterators
 ******************************************/
template <class T>
bool BSTIterator<T> :: operator == (const BSTIterator & rhs) const
{
   if (this->nodes.empty())
      return rhs.nodes.empty();
   return this->nodes.top() == rhs.nodes.top();
}

/**************************************************
 * BST ITERATOR :: INCREMENT POSTFIX
 * increment postfix operator
 *************************************************/
template <class T>
BSTIterator<T> BSTIterator<T> :: operator ++ (int postfix)
{
   BSTIterator<T> tmp(*this);
   ++*this;
   return tmp;
}

/**************************************************
 * BST ITERATOR :: INCREMENT PREFIX
 * increment prefix operator
 *************************************************/
template <class T>
BSTIterator <T> & BSTIterator <T> :: operator ++ ()
{
   // do nothing if we have nothing
   if (nodes.top() == NULL)
      return *this;

   // if there is a right node, take it
   if (nodes.top()->pRight != NULL)
   {
      nodes.push(nodes.top()->pRight);

      // there might be more left-most children
      while (nodes.top()->pLeft)
         nodes.push(nodes.top()->pLeft);
      return *this;
   }

   // there are no right children, the left are done
   assert(nodes.top()->pRight == NULL);
   BinaryNode <T> * pSave = nodes.top();
   nodes.pop();

   // if the parent is the NULL, we are done!
   if (NULL == nodes.top())
      return *this;

   // if we are the left-child, go to the parent.
   if (pSave == nodes.top()->pLeft)
      return *this;

   // we are the right-child, go up as long as we are the right child!
   while (nodes.top() != NULL && pSave == nodes.top()->pRight)
   {
      pSave = nodes.top();
      nodes.pop();
   }

   return *this;
}

/**************************************************
 * BST ITERATOR :: DECREMENT POSTFIX
 * decrement postfix operator
 *************************************************/
template <class T>
BSTIterator<T> BSTIterator<T> :: operator -- (int postfix)
{
   BSTIterator<T> tmp(*this);
   --*this;
   return tmp;
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
