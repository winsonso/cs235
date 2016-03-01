/***********************************************************************
* Header:
*    List
* Summary:
*    The list class holds a doubly-linked list of nodes. This file
*    also contains the Iterator for the list.
*
*    This will contain the class definition of:
*        Node         : Holds data and pointers to other nodes.
*        List         : Holds a collection of Nodes.
*        ListIterator : Used to iterate through a list.
* Author
*    Justin Waite & Winson So
************************************************************************/
#ifndef LIST_H
#define LIST_H

/******************************************
* NODE CLASS
* Holds data and pointers to other nodes.
*******************************************/
template <class T>
class Node
{
public:
   T data;
   Node<T> * pNext;
   Node<T> * pPrev;

   Node() : pNext(NULL), pPrev(NULL) { }
   Node(T data) : data(data), pNext(NULL), pPrev(NULL) { }
};

template <class T>
class ListIterator; // Iterator class

/*******************************************
* LIST CLASS
* The list class holds a doubly-linked list
* of nodes.
*******************************************/
template <class T>
class List
{
public:
   // default constructor
   List() throw (const char *);

   // copy constructor
   List(const List<T> & rhs) throw (const char *);

   // destructor
   ~List() {
      clear();
      delete pHead;
      delete pTail;
   }

   // Clears the list, deleting the pointers.
   void clear();

   // Checks if the list is empty by seeing if pHead points to pTail
   bool empty() const { return (pHead->pNext == pTail); }

   // Returns the number of items in the list.
   int size () const { return numItems; }

   // Adds an item onto the front of the list.
   void push_front(const T & data) throw (const char *);

   // Adds an item onto the back of the list.
   void push_back(const T & data) throw (const char *);

   // Copies the rhs list into this.
   List<T> & operator = (List<T> & rhs) throw (const char *);

   // Returns the item at the front of the list
   T & front() throw (const char *);

   // Returns the item at the back of the list
   T & back () throw (const char *);

   // Returns the first node in the list
   ListIterator<T> begin() const { return ListIterator<T>(pHead->pNext); }

   // Returns the past-last node in the list
   ListIterator<T> end() const { return ListIterator<T>(pTail); }

   // Returns the last node in the list
   ListIterator<T> rbegin() const { return ListIterator<T>(pTail->pPrev); }

   // Returns the before-first node in the list
   ListIterator<T> rend() const { return ListIterator<T>(pHead); }

   // Inserts an item into the list.
   ListIterator<T> insert(ListIterator<T> & pos, const T & t) throw (const char *);

   // Removes an item from the list.
   void remove(ListIterator<T> & pos) throw (const char *);

private:
   // The place-holding head node
   Node<T> * pHead;

   // The place-holding tail node
   Node<T> * pTail;

   // The number of items in the list.
   int numItems;

   // Attempts to allocate a new node.
   Node<T> * allocateNode(T t = T()) throw (const char *);
};

/**************************************************
 * List ITERATOR
 * An iterator through List
 *************************************************/
template <class T>
class ListIterator
{
public:

   // default constructor
   ListIterator() : p(NULL) {}

   // initialize to direct p to some item
   ListIterator(Node<T> * p) : p(p) {}

   // copy constructor
   ListIterator(const ListIterator & rhs) {
      *this = rhs;
   }

   // assignment operator
   ListIterator & operator = (const ListIterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // not equals operator
   bool operator != (const ListIterator & rhs) const
   {
      return rhs.p != this->p;
   }

   // equals operator
   bool operator = (const ListIterator & rhs) const
   {
      return rhs.p = this->p;
   }

   // eaual operator
   bool operator == (const ListIterator & rhs) const
   {
      return rhs.p == this->p;
   }

   // dereference operator
   T & operator * ()
   {
      return p->data;
   }

   // prefix increment
   ListIterator<T> & operator ++ ()
   {
      p = p->pNext;
      return *this;
   }

   // prefix decrement
   ListIterator<T> & operator -- ()
   {
      p = p->pPrev;
      return *this;
   }

   // postfix increment
   ListIterator<T> operator ++ (int postfix)
   {
      ListIterator tmp(*this);
      ++p;
      return tmp;
   }

   // postfix decrement
   ListIterator<T> operator -- (int postfix)
   {
      ListIterator tmp(*this);
      --p;
      return tmp;
   }

   friend ListIterator<T> List<T> :: insert(ListIterator<T> & pos, const T & t) throw (const char *);
   friend void List<T> :: remove(ListIterator<T> & pos) throw (const char *);

private:
   Node<T> * p;
};

/**************************************************
 * LIST :: ALLOCATE NODE
 * Attempts to allocate a new node.
 *************************************************/
template <class T>
Node<T> * List<T> :: allocateNode(T t) throw (const char *)
{
   Node<T> * node;
   try
   {
      node = new Node<T>(t);
   }
   catch(std::bad_alloc)
   {
     throw "ERROR: unable to allocate a new node for a list";
   }
   return node;
}

/**************************************************
 * LIST :: DEFAULT CONSTRUCTOR
 * Initializes the head and tail nodes and points
 * them to each other.
 *************************************************/
template <class T>
List<T> :: List() throw (const char *) : numItems(0)
{
   pHead = allocateNode();
   pTail = allocateNode();

   pHead->pNext = pTail;
   pTail->pPrev = pHead;
}

/**************************************************
 * LIST :: COPY CONSTRUCTOR
 * Initializes the head and tail nodes and copies
 * the rhs list.
 *************************************************/
template <class T>
List<T> :: List(const List<T> & rhs) throw (const char *)
{
   pHead = allocateNode();
   pTail = allocateNode();

   pHead->pNext = pTail;
   pTail->pPrev = pHead;

   for (ListIterator<T> it = rhs.begin(); it != rhs.end(); ++it)
   {
      T data = *it;
      this->push_back(data);
   }

   numItems = rhs.numItems;
}

/**************************************************
 * LIST :: CLEAR
 * Clears the list, deleting the pointers.
 *************************************************/
template <class T>
void List<T> :: clear()
{
   while (pHead->pNext != pTail)
   {
      Node<T> * temp = pHead->pNext;
      pHead->pNext = temp->pNext;
      delete temp;
   }
   pTail->pPrev = pHead;
   numItems = 0;
}

/**************************************************
 * LIST :: PUSH FRONT
 * Adds an item onto the front of the list.
 *************************************************/
template <class T>
void List<T> :: push_front(const T & data) throw (const char *)
{
   Node<T> * newNode = allocateNode(data);
   Node<T> * temp = pHead->pNext;

   newNode->pNext = temp;
   newNode->pPrev = pHead;
   temp->pPrev = newNode;
   pHead->pNext = newNode;

   numItems++;
}

/**************************************************
 * LIST :: PUSH BACK
 * Adds an item onto the back of the list.
 *************************************************/
template <class T>
void List<T> :: push_back(const T & data) throw (const char *)
{
   Node<T> * newNode = allocateNode(data);
   Node<T> * temp = pTail->pPrev;

   newNode->pNext = pTail;
   newNode->pPrev = temp;
   temp->pNext = newNode;
   pTail->pPrev = newNode;

   numItems++;
}

/**************************************************
 * LIST :: OPERATOR =
 * Copies the rhs list into this.
 *************************************************/
template <class T>
List<T> & List<T> :: operator = (List<T> & rhs) throw (const char *)
{
   this->clear();
   Node<T> * ptr = rhs.pHead->pNext;

   for (ListIterator<T> it = rhs.begin(); it != rhs.end(); ++it)
   {
      T data = *it;
      this->push_back(data);
   }

   this->numItems = rhs.numItems;
   return *this;
}

/**************************************************
 * LIST :: FRONT
 * Returns the item at the front of the list
 *************************************************/
template <class T>
T & List<T> :: front() throw (const char *)
{
   if (empty()) throw "ERROR: unable to access data from an empty list";
   return pHead->pNext->data;
}

/**************************************************
 * LIST :: BACK
 * Returns the item at the back of the list
 *************************************************/
template <class T>
T & List<T> :: back() throw (const char *)
{
   if (empty()) throw "ERROR: unable to access data from an empty list";
   return pTail->pPrev->data;
}

/**************************************************
 * LIST :: INSERT
 * Inserts an item into the list.
 *************************************************/
template <class T>
ListIterator<T> List<T> :: insert(ListIterator<T> & pos, const T & t) throw (const char *)
{
   Node<T> * newNode = allocateNode(t);

   Node<T> * pPrev = pos.p->pPrev;

   pPrev->pNext = newNode;
   newNode->pPrev = pPrev;
   pos.p->pPrev = newNode;
   newNode->pNext = pos.p;

   numItems++;

   return ListIterator<T>(newNode);
}

/**************************************************
 * LIST :: REMOVE
 * Removes an item from the list.
 *************************************************/
template <class T>
void List<T> :: remove(ListIterator<T> & pos) throw (const char *)
{
   if (pos == end() || pos == rend())
      throw "ERROR: unable to allocate a new node for a list";

   Node<T> * pPrev = pos.p->pPrev;
   Node<T> * pNext = pos.p->pNext;
   pPrev->pNext = pNext;
   pNext->pPrev = pPrev;

   numItems--;

   delete pos.p;
}

#endif //LIST_H
