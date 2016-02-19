/***********************************************************************
* Header:
*    List
* Summary:
*    This class contains  both a forward iterator and a reverse iterator,
*    it will be necessary to change our Node class to contain a pPrev pointer
*    as well as a pNext pointer.
*
*    This will contain the class definition of:
*        Node         : A class that holds a collection of data
         List
         ListIterator
* Author
*    Justin Waite & Winson So
************************************************************************/
#ifndef LIST_H
#define LIST_H
#define NULL_0

template <class T>
class Node; // Node class
template <class T>
class ListIterator; // Iterator class
/***************************************
* LIST CLASS
* To make a doubly-linked list and the
* pointerpoints to the previous node and
* the next node in the list
****************************************/
template<class T>
class List
{
public:
  // default constructor
  List(): items(0), pHead(NULL), pTail(NULL){}

  // copy constructor
  List(const List &rhs) throw(const char*);

  // destuctor
  ~List(){clear();}

  // size
  int size() {return items;}

  // clear
  void clear();

  // empty
  bool empty() {return !items;}

  // push_back
  void push_back(const T &t) throw(const char*);

  // push_front
  void push_front(const T &t) throw(const char*);

  // front
  T & front() throw(const char*);

  // back
  T & back() throw(const char*);

  // insert return iterator
  ListIterator<T> insert(ListIterator<T> location, const T& t) throw(const char*);

  // remove
  void remove(ListIterator<T> location) throw(const char*);

  // Return an iterator to the beginning/end of the LIST
  ListIterator<T> begin() {return ListIterator<T> (pHead); }
  ListIterator<T> end()
  {
    if(pTail == NULL)
      return ListIterator<T> (pTail);
    else
      return ListIterator<T> (pTail->pNext);
  }

  // Return a reverse iterator to the beginning/end of the LIST
  ListIterator<T> rbegin() {return ListIterator<T> (pTail); }
  ListIterator<T> rend()
  {
    if(pHead == NULL)
      return ListIterator<T> (pHead);
    else
      return ListIterator<T> (pHead->pPrev);
  }

private:
  int items;
  Node<T>* pHead;
  Node<T>* pTail;
};

/******************************************
* LIST: COPY CONSTRUCTOR
******************************************/
template <class T>
List<T>:: List(const List<T> &rhs) throw(const char*)
{
  if (rhs.pHead == NULL)
  {
    items = 0;
    pHead = NULL;
    pTail = NULL;
    return;
  }
  items = rhs.items;

  // copy all the node
  try
  {
    Node<T> *newHead = new Node<T>(rhs.pHead->data);
    pHead = newHead;
    Node<T> *newTail = new Node<T>(rhs.pTail->data);
    pTail = newTail;

    Node<T> *nextPtr = rhs.pHead->pNext;
    Node<T> *myPtr = pHead;
    while (nextPtr != NULL) {
      myPtr->pNext = new Node<T>(nextPtr->data);
      nextPtr = nextPtr->pNext;
      myPtr = myPtr->pNext;
    }

  }
  catch(std::bad_alloc)
  {
    throw "ERROR: unable to allocate a new node for a list";
  }
}

/******************************************
* LIST: clear()
* Empties the list of all items
******************************************/
template <class T>
void List<T>:: clear()
{
  if(pHead != NULL)
  {
    // To check each node if it is existed,
    // if it does, delete the node one by one
    Node<T>* tmp = pHead->pNext;
    while(tmp != NULL)
    {
      delete pHead;
      pHead = tmp;
      tmp = tmp->pNext;
    }
    delete pHead;
    pHead = NULL;
    pTail = NULL;
    items = 0;
  }
  else
  return;
}

/******************************************
* LIST: push_back()
* Adds an item to the back of the list
******************************************/
template <class T>
void List<T>::push_back(const T &t) throw(const char*)
{
  try
  {
    Node<T>* newData = new Node<T>(t);

    if(items == 0)
    {
      pHead = newData;
      pTail = newData;
      items++;
    }
    else
    {
      newData->pPrev = pTail;
      pTail->pNext = newData;
      pTail = newData;
      items++;
    }
  }
  catch(std::bad_alloc)
  {
    throw "ERROR: unable to allocate a new node for a list";
  }
}

/******************************************
* LIST: push_front()
* Adds an item to the front of the list
******************************************/
template <class T>
void List<T>::push_front(const T &t) throw(const char*)
{
  try
  {
    Node<T>* newData = new Node<T>(t);

    if(items == 0)
    {
      pHead = newData;
      pTail = newData;
    }
    else
    {
      pHead->pPrev    = newData;
      newData->pNext = pHead;
      pHead = newData;
    }
    items++;
  }
  catch(std::bad_alloc)
  {
    throw "ERROR: unable to allocate a new node for a list";
  }
}
/*****************************************************
* LIST: front()
* Returns the item currently at the front of the list
******************************************************/
template <class T>
T & List<T>::front() throw(const char*)
{
  try
  {
      if(items != 0)
      return pHead->data;
  }
  catch(std::bad_alloc)
  {
    throw "ERROR: unable to access data from an empty list";
  }
  return pHead->data; // it kept giving me warning so I duplicated the return value.
}

/*****************************************************
* LIST: back()
* Returns the item currently at the back of the list
******************************************************/
template <class T>
T & List<T>::back() throw(const char*)
{
  try
  {
      if(items != 0)
      return pTail->data;
  }
  catch(std::bad_alloc)
  {
    throw "ERROR: unable to access data from an empty list";
  }
  return pTail->data; // same here
}

/*****************************************************
* LIST: insert()
* Inserts an item in the middle of a list
******************************************************/
template <class T>
ListIterator<T> insert(ListIterator<T> location, const T& t) throw(const char*)
{
  try
  {
    Node<T>* newData = new Node<T>(t);
    if (location == NULL)
      push_back(t);
    else if (location.p->pPrev && location.p->pNext != NULL)
    {
      location.p->pPrev->pNext = newData;  // the (n-1)th node points to the new node
      newData->pPrev = location.p->pPrev;  // the new node points to (n-1)th node
      location.p->pPrev = newData;         // the pPrev of nth node points to new node
      newData->pNext = location.p;         // the new node points to nth node
      //items++;
      return ListIterator<T> (location.p->pPrev);
    }
    else
      push_front(t);
  }
  catch (std::bad_alloc)
  {
    throw "ERROR: unable to allocate a new node for a list";
  }
}

/*****************************************************
* LIST: remove()
* Removes an item from the middle of a list
******************************************************/
template <class T>
void List<T>::remove(ListIterator<T> location) throw(const char*)
{
  try
  {
    //that's the end
    if(location.p->pNext == NULL)
    {
      location.p->pPrev->pNext = NULL;
      pTail = location.p->pPrev;
      delete location.p;
    }
    // that's the front
    else if(location.p->pPrev == NULL)
    {
      pHead = location.p->pNext;
      pHead->pPrev = NULL;
      delete location.p;
    }
    //that's middle
    else
    {
      location.p->pPrev->pNext = location.p->pNext;
      location.p->pNext->pPrev = location.p->pPrev;
      delete location.p;
    }
    items--;
  }
  catch(std::bad_alloc)
  {
    throw "ERROR: unable to remove from an invalid location in a list";
  }
}
/******************************************
* NODE CLASS
* a pointer points to the pPrev and the
* other pointer points to the pNext
*******************************************/
template <class T>
class Node
{
  public:
   T data;
   Node<T>* pNext;
   Node<T>* pPrev;

   // default constructor taking initial value:
  Node() : pNext(NULL), pPrev(NULL){}

   // non-default constructor : pre-allocate
   Node(T temp) throw (const char *){
      data = temp;
      pNext = NULL;
      pPrev = NULL;
   }
};

/***********************
 * LISTITERATOR CLASS
 **********************/
template <class T>
class ListIterator
{
  public:
   // default constructor
   ListIterator() : p(0x00000000) {}

   // initialize to direct p to some item
   ListIterator(Node<T> * p) : p(p) {}

   // copy constructor
   ListIterator(const ListIterator & rhs) { *this = rhs;}

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
   bool operator = (const ListIterator &rhs) const
   {
     return rhs.p = this->p;
   }

   //equal operator
   bool operator == (const ListIterator &rhs) const
   {
     return rhs.p == this->p;
   }

   // dereference operator
   T & operator * () { return p->data; }

   // prefix increment
   ListIterator <T> & operator ++ ()
   {
      p = p->pNext;
      return *this;
   }

   ListIterator <T> & operator -- ()
   {
      p = p->pPrev;
      return *this;
   }

   // postfix increment
   ListIterator <T> operator++(int postfix)
   {
      ListIterator tmp(*this);
      ++p;
      return tmp;
   }

   // postfix increment
   ListIterator <T> operator--(int postfix)
   {
      ListIterator tmp(*this);
      --p;
      return tmp;
   }

   friend ListIterator <T> List<T>::insert(ListIterator<T> location , const T & t) throw(const char*);
   friend void List<T> :: remove(ListIterator<T> location) throw(const char*);

  private:
   Node<T> * p;
};

#endif //LIST_H
