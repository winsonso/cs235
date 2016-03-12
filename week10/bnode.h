/***********************************************************************
* Header:
*    Binary Node
* Summary:
*    The Binary Node class is to capture the notion of a single node in
*    a binary tree. There will br four member variables: a pointer to the
*    node to the right chind(pRight), a pointer to the node to the left
*    child(pLeft), a pointer to the parent (pParent), and the data
*    associated with the node.
*
*    This will contain the class definition of:
*        BinaryNode         : Holds data and pointers to other nodes.
* Author
*    Justin Waite & Winson So
************************************************************************/
#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <cassert>

using namespace std;

/*********************************************
* CLASS BINARY NODE
* A class that contains data and two pointers
* to children nodes, as well as a pointer to
* its parent node.
**********************************************/
template<class T>
class BinaryNode
{
public:
   BinaryNode() : pRight(NULL), pLeft(NULL), pParent(NULL), isRed(true),
                  isBlack(false) { }

   BinaryNode(const T &data) : data(data), pRight(NULL), pLeft(NULL),
                               isRed(true), isBlack(false), pParent(NULL) { }

   T data;
   BinaryNode<T> *pLeft;
   BinaryNode<T> *pRight;
   BinaryNode<T> *pParent;
   bool isRed;
   bool isBlack;

   BinaryNode<T> *addLeft(const T &t) throw(const char *);

   BinaryNode<T> *addRight(const T &t) throw(const char *);

   BinaryNode<T> *addLeft(BinaryNode<T> *rhs);

   BinaryNode<T> *addRight(BinaryNode<T> *rhs);

   int findDepth() const;

   void verifyRedBlack(int depth) const;

   void verifyBTree() const;

private:
   BinaryNode<T> *allocateNode(const T &t) throw(const char *);
};

/*********************************************
* allocateNode
* Attempts to allocate a new node, throwing
* an error if unsuccessful.
**********************************************/
template<class T>
BinaryNode<T> *BinaryNode<T>::allocateNode(const T &t) throw(const char *)
{
   BinaryNode<T> *newNode;
   try
   {
      newNode = new BinaryNode<T>(t);
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }
   return newNode;
}

/*********************************************
* addLeft()
* Adds a node to the left of the current node
**********************************************/
template<class T>
BinaryNode<T> *BinaryNode<T>::addLeft(const T &t) throw(const char *)
{
   BinaryNode<T> *newNode = allocateNode(t);
   pLeft = newNode;
   pLeft->pParent = this;
   return this;
}

/*********************************************
* addLeft()
* Adds a node to the left of the current node
**********************************************/
template<class T>
BinaryNode<T> *BinaryNode<T>::addLeft(BinaryNode<T> *rhs)
{
   this->pLeft = rhs;
   if (rhs != NULL)
   { rhs->pParent = this; }
   return this;
}

/*********************************************
* addRight()
* Adds a node to the right of the current node
**********************************************/
template<class T>
BinaryNode<T> *BinaryNode<T>::addRight(const T &t) throw(const char*)
{
   BinaryNode<T> *newNode = allocateNode(t);
   pRight = newNode;
   pRight->pParent = this;
   return this;
}

/*********************************************
* addRight()
* Adds a node to the right of the current node
**********************************************/
template<class T>
BinaryNode<T> *BinaryNode<T>::addRight(BinaryNode<T> *rhs)
{
   this->pRight = rhs;
   if (rhs != NULL)
      rhs->pParent = this;
   return this;
}

/**********************************************
* deleteBinaryTree()
* Takes a BinaryNode as a parameter and deletes
* all the children and itself
***********************************************/
template<class T>
void deleteBinaryTree(BinaryNode<T> *rhs)
{
   if (rhs == NULL) return;
   if (rhs->pLeft != NULL)
      deleteBinaryTree(rhs->pLeft);
   if (rhs->pRight != NULL)
      deleteBinaryTree(rhs->pRight);

   delete rhs;
}

/****************************************************
 * BINARY NODE :: FIND DEPTH
 * Find the depth of the black nodes. This is useful for
 * verifying that a given red-black tree is valid
 ****************************************************/
template<class T>
int BinaryNode<T>::findDepth() const
{
   // if there are no children, the depth is ourselves
   if (pRight == NULL && pLeft == NULL)
      return (isRed ? 0 : 1);

   // if there is a right child, go that way
   if (pRight != NULL)
      return (isRed ? 0 : 1) + pRight->findDepth();
   else
      return (isRed ? 0 : 1) + pLeft->findDepth();
}

/****************************************************
 * BINARY NODE :: VERIFY RED BLACK
 * Do all four red-black rules work here?
 ***************************************************/
template<class T>
void BinaryNode<T>::verifyRedBlack(int depth) const
{
   depth -= (!isRed) ? 1 : 0;

   // Rule a) Every node is either red or black
   assert(isRed || !isRed); // this feels silly

   // Rule b) The root is black
   if (pParent == NULL)
      assert(!isRed);

   // Rule c) Red nodes have black children
   if (isRed)
   {
      if (pLeft != NULL)
         assert(!pLeft->isRed);
      if (pRight != NULL)
         assert(!pRight->isRed);
   }

   // Rule d) Every path from a leaf to the root has the same # of black nodes
   if (pLeft == NULL && pRight && NULL)
      assert(depth == 0);
   if (pLeft != NULL)
      pLeft->verifyRedBlack(depth);
   if (pRight != NULL)
      pRight->verifyRedBlack(depth);
}

/******************************************************
 * VERIFY B TREE
 * Verify that the tree is correctly formed
 ******************************************************/
template<class T>
void BinaryNode<T>::verifyBTree() const
{
   // check parent
   if (pParent)
      assert(pParent->pLeft == this || pParent->pRight == this);

   // check left
   if (pLeft)
   {
      assert(pLeft->data <= data);
      assert(pLeft->pParent == this);
      pLeft->verifyBTree();
   }

   // check right
   if (pRight)
   {
      assert(pRight->data >= data);
      assert(pRight->pParent == this);
      pRight->verifyBTree();
   }
}

#endif // BST_H
