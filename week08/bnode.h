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

/*****************************************
* BINARY NODE CLASS
* Holds data and pointers to other nodes.
******************************************/
template <class T>
class BinaryNode
{
public:
  T data;
  BinaryNode<T>* pRight;
  BinaryNode<T>* pLeft;
  BinaryNode<T>* pParent;

  BinaryNode(): pRight(NULL), pLeft(NULL), pParent(NULL) {}
  BinaryNode(T data): data(data), pRight(NULL), pLeft(NULL), pParent(NULL) {}

  BinaryNode<T>* addLeft(const T& t) throw (const char*);
  BinaryNode<T>* addRight(const T& t) throw (const char*);
  BinaryNode<T>* addLeft(BinaryNode<T>* rhs);
  BinaryNode<T>* addRight(BinaryNode<T>* rhs);
};

/*********************************************
* addLeft()
* Adds a node to the left of the current node
**********************************************/
template <class T>
BinaryNode<T>* BinaryNode<T>::addLeft(const T& t) throw (const char*)
{
  try
  {
     BinaryNode<T>* newData = new BinaryNode<T> (t);
     pLeft = newData;
     pLeft->pParent = this;
  }
  catch(std::bad_alloc)
  {
     throw "ERROR: Unable to allocate a node";
  }
  return this;
}

/*********************************************
* addRight()
* Adds a node to the right of the current node
**********************************************/
template <class T>
BinaryNode<T>* BinaryNode<T>::addRight(const T& t) throw (const char*)
{
  try
  {
     BinaryNode<T>* newData = new BinaryNode<T> (t);
     pRight = newData;
     pRight->pParent = this;
  }
  catch(std::bad_alloc)
  {
     throw "ERROR: Unable to allocate a node";
  }
  return this;
}

/*********************************************
* addRight()
* Adds a node to the right of the current node
**********************************************/
template <class T>
BinaryNode<T>* BinaryNode<T>::addRight(BinaryNode<T>* rhs)
{
  this->pRight = rhs;
  if (rhs != NULL) { rhs->pParent = this;}
  return this;
}

/*********************************************
* addLeft()
* Adds a node to the left of the current node
**********************************************/
template <class T>
BinaryNode<T>* BinaryNode<T>::addLeft(BinaryNode<T>* rhs)
{
  this->pLeft = rhs;
  if (rhs != NULL) { rhs->pParent = this;}
  return this;
}

/**********************************************
* deleteBinaryTree()
* Takes a BinaryNode as a parameter and deletes
* all the children and itself
***********************************************/
template <class T>
void deleteBinaryTree(BinaryNode<T>* rhs)
{
  if(rhs->pLeft == NULL && rhs->pRight == NULL)
     delete rhs;
  else
  {
     if(rhs->pLeft != NULL)
        deleteBinaryTree(rhs->pLeft);
     if(rhs->pRight != NULL)
        deleteBinaryTree(rhs->pRight);
  }
}

/**********************************************
* Insertion operator
* This is a recursive function traversing the
* tree in infix order. A single space will be
* displayed after every element.
***********************************************/
template <class T>
std::ostream & operator <<(std::ostream & out, const BinaryNode<T>* tree)
{
   if (tree != NULL)
   {
      if (tree->pLeft != NULL)
      {
         std::cout<<tree->pLeft;
      }
      out << tree->data<< ' ';
      if (tree->pRight != NULL)
      {
         std::cout<<tree->pRight;
      }
   }
   return out;
}
#endif
