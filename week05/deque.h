/***********************************************************************
* Header:
*    Deque
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
#ifndef DEQUE_H
#define DEQUE_H

#include <cassert>
#include <iostream>
/************************************************
 * DEQUE CLASS
 * A container that holds data in a "deque"
 * pattern. The data can be accessed from
 * the both side of the deque.
 ***********************************************/
template <class T>
class Deque
{
public:
	// default constructor : set to empty
	Deque() : numItems(0), capac(0), frontNum(0), backNum(0), data(0x00000000) {}

	// copy constructor : copy the deque class
	Deque(const Deque & rhs) throw (const char *);

	// non-default constructor : pre-allocate
	Deque(int capac) throw (const char *);

    // destructor : free everything
	~Deque()
	{
		if(capac > 0)
		delete[] data;
	}

   // is the container currently empty
   bool empty() const  { return numItems == 0;         }

    // how many items are currently in the container?
   int size() const    { return numItems;              }

   // capacity
   int capacity() const { return capac; }

   // remove all the items from the container
   void clear()        { numItems = 0;frontNum = 0; backNum = 0; }

   // Adds an item to the back of the deque
   void push_back(const T &t) throw (const char*);

   // Adds an item to the front of the deque
   void push_front(const T &t) throw (const char*);

   // Removes an item from the front of the deque
   void pop_front() throw (const char*) ;

   // Removes an item from the back of the deque
   void pop_back() throw (const char*);

   // Returns the item currently at the front of the deque
   T& front() throw (const char*);

   // Returns the item currently at the back of the deque.
   T& back() throw (const char*);

   void print() {
      std::cout << "current data:" << std::endl;
      for (int i = 0; i < capac; i++)
      {
         if (i == frontNum)
            std::cout << "[f]" << data[i] << std::endl;
         else if (i == backNum)
            std::cout << "[b]" << data[i] << std::endl;
         else
            std::cout << "[" << i << "]" << data[i] << std::endl;
      }
      std::cout << "numItems: " << numItems << std::endl;
      if (!empty())
         std::cout << "front: " << front() << std::endl;
   }

private:
   T * data;          // dynamically allocated array of T
   int numItems;      // how many items are currently in the Container?
   int capac;         // how many items can I put on the Container before full?
   int frontNum;      // index of the front item
   int backNum;       // index of the back item

   void resize(int newCapac);
};

/**********************************************
 * DEQUE : RESIZE
 * Attempts to resize the data array to
 * newCapac. Will not downsize, only upsize.
 **********************************************/
template <class T>
void Deque<T> :: resize(int newCapac)
{
  if (capac >= newCapac)
    return;

   // attempt to allocate
   try
   {
      // Just need to allocate new array without copying anything.
      if (capac == 0)
      {
         data = new T[newCapac];
         backNum = 0;
      }

      // There were items before, so allocate new and copy old.
      else
      {
         T* temp = data;
         data = new T[newCapac];
         if (numItems > 0)
         {
            int i = 0;
            for(int iOld = frontNum; i < numItems; iOld = (iOld + 1) % capac)
               data[i++] = temp[iOld];
            backNum = i - 1;
         }
         delete[] temp;
      }
       capac = newCapac;
       frontNum = 0;
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for deque";
   }
}

/*******************************************
 * DEQUE :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Deque <T> :: Deque(const Deque <T> & rhs) throw (const char *) : capac(0),
   numItems(0), frontNum(0), backNum(0)
{
   assert(rhs.capac >= 0);

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
   for (int iRhs = rhs.frontNum; i < numItems; iRhs = (iRhs + 1) % rhs.capac)
      data[i++] = rhs.data[iRhs];

   // the rest needs to be filled with the default value for T
   for (int i = backNum + 1; i < capac; i++)
      data[i] = T();
}

/**********************************************
 * DEQUE : NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Deque<T> :: Deque(int capac) throw (const char *) : capac(0), numItems(0),
   frontNum(0), backNum(0)
{
   assert(capac >= 0);

   // Set data to empty and return.
   if (capac == 0)
   {
      this->data = 0x00000000;
      return;
   }

   // attempt to allocate
   resize(capac);

   // initialize the container by calling the default constructor for each item
   for (int i = 0; i < capac; i++)
      data[i] = T();
}

/******************************************************
 *  push_front:  Adds an item to the front of the deque
 ******************************************************/
template <class T>
void Deque<T>::push_front(const T &t) throw (const char*)
{
   // If we need to increase capacity, do it.
   if (capac == 0)
      resize(1);
   else if (numItems == capac)
      resize(capac * 2);

   // Decrease the frontNum index and wrap around if needed.
   if (numItems > 0)
      frontNum = (frontNum - 1 < 0) ? capac - 1 : frontNum - 1;

   // Insert new item to front.
   data[frontNum] = t;
   numItems++;
}

/******************************************************
 *  push_back:  Adds an item to the back of the deque
 ******************************************************/
template <class T>
void Deque<T>::push_back(const T& t) throw (const char*)
{
   // If we need to increase capacity, do it.
   if (capac == 0)
      resize(1);
   else if(numItems == capac)
      resize(capac * 2);

   // Increase the backNum index and wrap around if needed.
   if (numItems > 0)
      backNum = (backNum + 1) % capac;

   // Insert new item to back.
   data[backNum] = t;
   numItems++;
}

/*****************************************************
 *  pop_back: Removes an item from the back of the
 *           deque, serving to reduce the size by one.
 ****************************************************/
template <class T>
void Deque<T>::pop_back() throw (const char*)
{
   if(empty())
      throw"ERROR: unable to pop from the back of empty deque";

   numItems--;

   // Decrease the backNum, wrapping if needed.
   if (numItems > 0)
      backNum = (backNum - 1 < 0) ? capac - 1 : backNum - 1;
}

/*****************************************************
 *  pop_front: Removes an item from the front of the
 *           deque, serving to reduce the size by one.
 ****************************************************/
template <class T>
void Deque<T>::pop_front() throw (const char*)
{
   if(empty())
      throw "ERROR: unable to pop from the front of empty deque";

   numItems--;
   // Increase the frontNum, wrapping if needed.
   if (numItems > 0)
      frontNum = (frontNum + 1) % capac;
}

/**************************************************************
 *  Front: Returns the item currently at the front of the deque
 *************************************************************/
template <class T>
T& Deque<T>::front() throw (const char*)
{
   if(this->empty())
      throw"ERROR: unable to access data from an empty deque";
   return data[frontNum];
}

 /**************************************************************
  *  Back: Returns the item currently at the back of the deque
  *************************************************************/
template <class T>
T& Deque<T>::back() throw (const char*)
{
   if(this->empty())
      throw"ERROR: unable to access data from an empty deque";
   return data[backNum];
}

#endif // DEQUE_H
