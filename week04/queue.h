/***********************************************************************
* Header:
*    Queue
* Summary:
*    This class contains the the Queue ADT which is FIFO. A queue holds
*    a list of any data type and has different methods for modifying the
*    list. One can remove an item from the head of queue (pop), add an item
*    to the container (push), return the item currently at the front of
*    the queue (front), and returns the item currently at the back of the
*    queue (back).
*
*    This will contain the class definition of:
*        Queue         : A class that holds a collection of data
* Author
*    Justin Waite & Winson So
************************************************************************/
#ifndef QUEUE_H
#define QUEUE_H

#include <cassert>

/************************************************
 * QUEUE
 * A container that holds data in a "queue"
 * pattern. The data can only be accessed from
 * the first of the queue. First in, first out.
 ***********************************************/
 template <class T>
class Queue
{
public:
   // default constructor
   Queue() : numItems(0), capac(0), frontNum(0) ,backNum(0), data(0x00000000) { }

   // copy constructor : copy the queue class
   Queue(const Queue & rhs) throw (const char*);

   // non-default constructor : pre-allocate
   Queue(int capac) throw (const char*);

   // destructor : free everything
   ~Queue()
   {
      if (capac > 0)
         delete [] data;
   }

   // is the queue currently empty
   bool empty()   const { return numItems == 0; }

   // how many items are currently in the queue?
   int size()     const { return numItems;      }

   // return the current capacity of the queue
   int capacity() const { return capac;         }

   // empties the queue of all items
   void clear()         { numItems = 0; frontNum = 0; backNum = 0;}

   // push an item onto the queue
   void push(const T &t) throw (const char*);

   // pop the head item off in the queue
   void pop() throw (const char*);

   // returns the item currently at the back of the queue
   T & back() throw (const char*);

   // returns the item currently at the front of the queue.
   T & front() throw (const char*);


   // assignment operator
   Queue<T>& operator = (const Queue<T> &rhs);

private:
   T* data;           // dynamically allocated array of T
   int numItems;      // how many items are currently in the Container?
   int capac;         // how many items can I put on the Container before full?
   int frontNum;
   int backNum;

   void resize(int newCapac);
};


/**********************************************
 * QUEUE : RESIZE
 * Attempts to resize the data array to
 * newCapac. Will not downsize, only upsize.
 **********************************************/
template <class T>
void Queue<T> :: resize(int newCapac)
{
   if (capac >= newCapac)
      return;

   // attempt to allocate
   try
   {
      if (capac == 0)
         data = new T[newCapac];
      else
      {
         T* temp = data;
         data = new T[newCapac];
         for(int i = 0; i < numItems; i++)
            data[i] = temp[i];
         delete[] temp;
      }

      capac = newCapac;
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for queue";
   }
}

/*******************************************
 * QUEUE :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Queue <T> :: Queue(const Queue <T> & rhs) throw (const char *)
{
   assert(rhs.capac >= 0);
   capac = numItems = 0;

   // do nothing if there is nothing to do
   if (rhs.capac == 0)
   {
      data = 0x00000000;
      return;
   }

   resize(rhs.capac);

   // copy over the capacity and size
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.capac);
  numItems = rhs.numItems;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numItems; i++)
      data[i] = rhs.data[i];

   // the rest needs to be filled with the default value for T
   for (int i = numItems; i < capac; i++)
      data[i] = T();
}

/**********************************************
 * QUEUE : NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Queue<T> :: Queue(int capac) throw (const char *)
{
   assert(capac >= 0);
   this->capac = 0;

   // do nothing if there is nothing to do
   if (capac == 0)
   {
      this->data = 0x00000000;
      return;
   }

   // attempt to allocate
   resize(capac);

   // copy over the stuff
   this->capac = capac;

   // Set number of items to zero
    this->numItems = 0;

   // initialize the container by calling the default constructor for each item
   for (int i = 0; i < capac; i++)
      data[i] = T();
}

/**********************************************
 * QUEUE : ASSIGNMENT OPERATOR
 * Sets the queue to a new copy of the rhs.
 **********************************************/
template <class T>
Queue<T>& Queue<T> :: operator = (const Queue<T> &rhs)
{
   if (this == &rhs)
   {
      return *this;
   }

   if (rhs.numItems > capac)
   {
      resize(rhs.capac);
   }

   numItems = rhs.numItems;

   //copy over the items individually
   for (int i = 0; i < numItems; i++)
   {
      data[i] = rhs.data[i];
   }

   return *this;
}

/*********************************************
 *  push: Adds an item to the queue
 ********************************************/
template <class T>
void Queue<T> :: push(const T &t) throw (const char*)
{
  try
  {
   if(capac == 0 )
   {
      capac = 1;
      data = new T[capac];
   }
   // if we dont have enough space, do stuff
   else if (numItems == capac)
   {
      T*temp = data;
      capac = capac * 2;
      data = new T[capac];
            int i = 0;
      for (int k = frontNum; k < numItems; k = (k + 1) % (capac / 2))
      {
         data[i] = temp[k];
         i++;
      }
      delete [] temp;
       frontNum = 0;
       backNum = numItems;
   }

   //here comes the insert part
   data[backNum] = t;
   backNum = (backNum + 1) % capac;
   numItems++;
 }
 catch (std::bad_alloc)
 {
   throw "ERROR: Unable to allocate a new buffer for queue";
 }

}

/*********************************************
 *  Pop: Removes an item from the head of the
 *  queue, serving to reduce the size by one.
 *********************************************/
template <class T>
void Queue<T> :: pop() throw (const char*)
{
   try
   {
      if(this->empty())
      {
         throw "ERROR: attempting to pop from an empty queue";
      }
      else
         frontNum = (frontNum + 1) % capac;
         numItems--;
   }
   catch(std::bad_alloc)
   {
     throw "ERROR: attempting to pop from an empty queue";
   }
}

/*********************************************
 *  Back: Returns the item currently at the
 *       back of the queue
 *********************************************/
template <class T>
T& Queue<T> :: back() throw (const char*)
{
 try
   {
      if(this->empty())
      {
         throw "ERROR: attempting to access an item in an empty queue";
      }
      if (backNum == 0)
         return data[capac - 1];
      else
         return data[backNum - 1];
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: attempting to access an item in an empty queue";
   }
}

/*********************************************
 *  Front: Returns the item currently at the
 *         front of the queue
 *********************************************/
 template <class T>
 T& Queue<T> :: front() throw (const char*)
 {
    try
   {
      if(this->empty())
      {
         throw "ERROR: attempting to access an item in an empty queue";
      }
      return data[frontNum];
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: attempting to access an item in an empty queue";
   }
 }
#endif // QUEUE_H
