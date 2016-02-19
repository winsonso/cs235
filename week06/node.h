/***********************************************************************
* Header:
*    Node
* Summary:
*    This class encapsulates the notion of a linked-list Node.
*    A linked-list holds a list of any data type and has different methods
*    for modifying the list. One can copy a linked-list(copy), insert
*    a new Node into the current linked-list (insert), Find the Node
*    corresponding to a given passed value from a given linked-list (find),
*    and Release all the memory contained in a given linked-list (freeData).
*
*    This will contain the class definition of:
*        Node         : A class that holds a collection of data
* Authors
*    Justin Waite & Winson So
************************************************************************/
#ifndef NODE_H
#define NODE_H

#include <iostream>

/****************************************
* NODE CLASS
* Used to make a linked-list; the pointer
* points to the next node in the list
*****************************************/
template <class T>
class Node
{
public:
   T data;
   Node<T>* pNext;

   // default constructor, sets pNext to NULL
   Node() : pNext(NULL) {}

   // non-default constructor : sets data to temp and pNext to NULL
   Node(T temp) throw (const char *);
};

/**********************************************
 * NODE : NON-DEFAULT CONSTRUCTOR
 * Sets the data to temp and pNext to NULL
 **********************************************/
template <class T>
Node <T> :: Node(T temp) throw (const char *)
{
   data = temp;
   pNext = NULL;
}

/*****************************************************
COPY
 * Copy a linked-list. Takes a pointer to a Node as
 * a parameter and returns a newly created linked-list
 * containing a copy of all the nodes below the list
 * represented by the parameter.
 *****************************************************/
template <class T>
Node<T>* copy(Node<T>* first)
{
   if(first == NULL)
      return NULL;
   Node<T>* newfirst;

   //  allocate the first spot
   Node<T>* tmp;
   tmp = new Node<T>();
   newfirst = tmp;

   for(Node<T>* p = first; p; p = p->pNext)
   {
      if(p->pNext == NULL)
      {
         tmp->data = p->data;
         tmp->pNext = NULL;
      }
      else
      {
         tmp->data = p->data;
         tmp->pNext = new Node<T>();
         tmp = tmp->pNext;
      }
   }
   return newfirst;
}

/**********************************************
FREE DATA
 * Release all the memory contained in a given
 * linked-list. The one parameter is a pointer
 * to the head of the list.
 **********************************************/
template <class T>
void freeData(Node<T>* & first)
{
   if(first != NULL)
   {
      Node<T>* tmp = first->pNext;
      while(tmp != NULL)
      {
         delete first;
         first = tmp;
         tmp = tmp->pNext;
      }
      delete first;
      first = NULL;
   }
}

/*******************************************************
 * Display the contents of a given linked-list.
 * This will output a comma separated list of the
 * data items, if there is more than one item in the list.
 *******************************************************/
template <class T>
std::ostream & operator << (std::ostream & output, const Node<T> * pHead)
{
   if (pHead != NULL)
   {
      const Node<T> * p = pHead;
      while(p->pNext != NULL)
      {
         output<< p->data<<", ";
         p = p->pNext;
      }
      output<<p->data;
   }
   return output;
}

/*****************************************************
 * Insert a new Node into the current linked-list.
 * The first parameter is the value to be placed in
 * the new Node. The second parameter is the Node
 * preceding the new Node in the list. An optional
 * third parameter is set to true if the new item is
 * to be at the head of the list.
 *****************************************************/
template <class T>
void insert(T toAdd, Node<T>* & precNode, bool isHead=false)
{
   if(!isHead && precNode != NULL)
   {
      Node<T>* tmp = new Node<T>(toAdd);
      tmp->pNext = precNode->pNext;
      precNode->pNext = tmp;
   }
   else
   {
      Node<T>* tmp = new Node<T>(toAdd);
      tmp->pNext = precNode;
      precNode = tmp;
   }
}

/*****************************************************
 * Find the Node corresponding to a given passed value
 * from a given linked-list, . The first parameter is
 * a pointer to the front of the list, the second is
 * the value to be found. The return value is a pointer
 * to the found node if one exists.
 *****************************************************/
template <class T>
Node<T>* find(Node<T>* pHead, const T & item)
{
   while(pHead)
   {
      if (pHead->data == item)
         return pHead;
      pHead = pHead->pNext;
   }
   return NULL;
}

#endif
