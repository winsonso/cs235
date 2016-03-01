#ifndef BTREE_H
#define BTREE_H

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
   if (rhs != NULL) { rhs->pParent = this;}
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

#endif // BST_H
