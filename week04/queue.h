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
   T & back() const throw (const char*);

   // returns the item currently at the front of the queue.
   T & front() const throw (const char*);

   // assignment operator
   Queue<T>& operator = (const Queue<T> &rhs);

private:
   T* data;           // dynamically allocated array of T
   int numItems;      // how many items are currently in the Container?
   int capac;         // how many items can I put on the Container before full?
   int frontNum;      // index of the front item
   int backNum;       // index of the back item

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
         if (numItems > 0)
         {
            int i = 0;
            for(int k = frontNum; i < numItems; k = (k + 1) % capac)
               data[i++] = temp[k];
            backNum = i - 1;
         }
         delete[] temp;
      }

      capac = newCapac;
      frontNum = 0;
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
   capac = numItems = frontNum = backNum = 0;

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
   backNum = rhs.numItems - 1;

   // copy the items over one at a time using the assignment operator
   int i = 0;
   for (int k = rhs.frontNum; i < numItems; k = (k + 1) % rhs.capac)
      data[i++] = rhs.data[k];

   // the rest needs to be filled with the default value for T
   for (int i = backNum + 1; i < capac; i++)
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

   // set defaults
   numItems = 0;
   frontNum = 0;
   backNum = 0;

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
   frontNum = rhs.frontNum;
   backNum = rhs.backNum;

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
         capac = 2;
         data = new T[capac];
      }

      // if we dont have enough space, resize to double capacity.
      else if (numItems == capac)
      {
         resize(capac * 2);
      }

      //here comes the insert part
      if (numItems > 0)
         backNum = (backNum + 1) % capac;
      data[backNum] = t;
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
   if(empty())
   {
      throw "ERROR: attempting to pop from an empty queue";
   }

   if (numItems - 1 > 0)
      frontNum = (frontNum + 1) % capac;
   numItems--;
}

/*********************************************
 *  Back: Returns the item currently at the
 *  back of the queue
 *********************************************/
template <class T>
T& Queue<T> :: back() const throw (const char*)
{
   if(this->empty())
   {
      throw "ERROR: attempting to access an item in an empty queue";
   }

   return data[backNum];
}

/*********************************************
 *  Front: Returns the item currently at the
 *  front of the queue
 *********************************************/
 template <class T>
 T& Queue<T> :: front() const throw (const char*)
 {
   if(this->empty())
   {
      throw "ERROR: attempting to access an item in an empty queue";
   }
   return data[frontNum];
 }
#endif // QUEUE_H
