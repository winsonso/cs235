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
using namespace std;

template <class T>
class BinaryNode
{
public:
  BinaryNode(): pRight(NULL), pLeft(NULL), pParent(NULL) {}
  BinaryNode(T data): data(data), pRight(NULL), pLeft(NULL), pParent(NULL) {}

  T data;
  BinaryNode<T> * pLeft;
  BinaryNode<T> * pRight;
  BinaryNode<T> * pParent;

  BinaryNode<T> * addLeft(const T & t) throw (const char *);
  BinaryNode<T> * addRight(const T & t) throw (const char *);
  BinaryNode<T> * addLeft(BinaryNode<T> * rhs);
  BinaryNode<T> * addRight(BinaryNode<T> * rhs);

private:
   BinaryNode<T> * allocateNode(const T & t) throw (const char *);
};

/*********************************************
* allocateNode
* Attempts to allocate a new node, throwing
* an error if unsuccessful.
**********************************************/
template <class T>
BinaryNode<T> * BinaryNode<T> :: allocateNode(const T & t) throw (const char *)
{
   BinaryNode<T> * newNode;
   try
   {
      newNode = new BinaryNode<T>(t);
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }
   return newNode;
}

/*********************************************
* addLeft()
* Adds a node to the left of the current node
**********************************************/
template <class T>
BinaryNode<T> * BinaryNode<T> :: addLeft(const T & t) throw (const char *)
{
   BinaryNode<T> * newNode = allocateNode(t);
   pLeft = newNode;
   pLeft->pParent = this;
   return this;
}

/*********************************************
* addLeft()
* Adds a node to the left of the current node
**********************************************/
template <class T>
BinaryNode<T> * BinaryNode<T> :: addLeft(BinaryNode<T> * rhs)
{
   this->pLeft = rhs;
   if (rhs != NULL) { rhs->pParent = this;}
   return this;
}

/*********************************************
* addRight()
* Adds a node to the right of the current node
**********************************************/
template <class T>
BinaryNode<T> * BinaryNode<T>::addRight(const T& t) throw (const char*)
{
   BinaryNode<T> * newNode = allocateNode(t);
   pRight = newNode;
   pRight->pParent = this;
   return this;
}

/*********************************************
* addRight()
* Adds a node to the right of the current node
**********************************************/
template <class T>
BinaryNode<T> * BinaryNode<T> :: addRight(BinaryNode<T>* rhs)
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
template <class T>
void deleteBinaryTree(BinaryNode<T> * rhs)
{
   if (rhs == NULL) return;
   if(rhs->pLeft != NULL)
      deleteBinaryTree(rhs->pLeft);
   if(rhs->pRight != NULL)
      deleteBinaryTree(rhs->pRight);

   delete rhs;
}

#endif // BST_H
