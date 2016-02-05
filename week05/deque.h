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
	// default constructor : empty and kinda useless
	Deque() : numItems(0), capac(0), frontNum(0), backNum(0), data(0x00000000), input(false) {}

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
   int capacity() const {return capac;}

   // remove all the items from the container
   void clear()        { numItems = 0;frontNum =0; backNum = 0;}

   // Adds an item to the back of the deque
   void push_back(const T &t) throw (const char*);

   // Adds an item to the front of the deque
   void push_front(const T &t) throw (const char*);

   // Removes an item from the front of the deque
   void pop_front() throw (const char*) ;

   // Removes an item from the back of the deque
   void pop_back() throw (const char*);

   // Returns the item currently at the front of the deque
   T front() throw (const char*);

   // Returns the item currently at the back of the deque.
   T back() throw (const char*);

   // Assignment operator
   Deque<T> & operator = (const Deque<T> &rhs);

private:
   T * data;          // dynamically allocated array of T
   int numItems;      // how many items are currently in the Container?
   int capac;         // how many items can I put on the Container before full?
   int frontNum;      // index of the front item
   int backNum;       // index of the back item
   bool input;        // to check if it is entered

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
      throw "ERROR: Unable to allocate a new buffer for deque";
   }
}

/*******************************************
 * DEQUE :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Deque <T> :: Deque(const Deque <T> & rhs) throw (const char *)
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
 * DEQUE : NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Deque<T> :: Deque(int capac) throw (const char *)
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
 * DEQUE : ASSIGNMENT OPERATOR
 * Sets the queue to a new copy of the rhs.
 **********************************************/
template<class T>
Deque<T> & Deque<T>::operator = (const Deque<T> &rhs)
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

/******************************************************
 *  push_front:  Adds an item to the front of the deque
 ******************************************************/
template <class T>
void Deque<T>::push_front(const T &t) throw (const char*)
{
try
{
   input = true;
   if(numItems == 0 )
   {
      if (capac == 0)
      {
         capac = 1;
         data = new T [capac];
      }
      data[0] = t;
      backNum =1;
      numItems++;
      frontNum = 0;
      return;
   }
   //frontNum = frontNum -1;
   if(numItems == capac)
   {
      T*temp = data;
      capac = capac*2;
      data = new T[capac];
      int i = 0;
      for (int j = frontNum; i < numItems; j = (j +1)%(capac/2))
      {
         data[i] = temp[j];
         i++;
      }
      delete[] temp;
      frontNum = 0;
      backNum = numItems;
   }

   if (frontNum == 0 && numItems > 0)
   {
      if (numItems != capac)
      {
      frontNum = capac -1;
      data[frontNum] = t;
      numItems++;
      }
      return;
      }
   data[frontNum -1] = t;
   frontNum--;
   numItems++;
  }
  catch (std::bad_alloc)
  {
  	throw "ERROR: Unable to allocate a new buffer for deque";
  }
}

/******************************************************
 *  push_back:  Adds an item to the back of the deque
 ******************************************************/
template <class T>
void Deque<T>::push_back(const T &t) throw (const char*)
{
try
	{
   if(numItems == 0 )
   {
      if (capac == 0)
      {
         capac = 1;
         data = new T [capac];
      }
      data[0] = t;
      frontNum = capac;
      backNum = 1;
      numItems++;
      return;
   }

   // check if we dont have enough space
   if(numItems == capac)
   {
      T*temp = data;
      capac = capac*2;
      data = new T[capac];
      int i = 0;
      for (int j = frontNum; i < numItems; j = (j +1)%(capac/2))
      {
         data[i] = temp[j];
         i++;
      }
      delete[] temp;
      frontNum = 0;
      backNum = numItems;
   }

   //the insert part
   if(numItems != capac)
   {
      data[backNum] = t;
   }

   backNum = (backNum + 1) % capac;
   numItems++;
   }
   catch (std::bad_alloc)
  {
  	throw "ERROR: Unable to allocate a new buffer for deque";
  }
}

/*****************************************************
 *  pop_back: Removes an item from the back of the
 *            deque, serving to reduce the size by one.
 ****************************************************/
template <class T>
void Deque<T>::pop_back() throw (const char*)
{
    if(!this->empty())
    {
       backNum = (backNum -1)%capac;
       numItems--;
       if(backNum == 0)
       {
          backNum = capac;
       }
    }
    else
        throw"ERROR: unable to pop from the back of empty deque";
}

/*****************************************************
 *  pop_front: Removes an item from the front of the
 *            deque, serving to reduce the size by one.
 ****************************************************/
template <class T>
void Deque<T>::pop_front() throw (const char*)
{
    if(!this->empty())
    {
       if(frontNum == capac -1)
          frontNum = 0;
       else
       {
       	frontNum = (frontNum + 1)% capac;
       }
       numItems--;
    }
    else
        throw "ERROR: unable to pop from the front of empty deque";
}

/**************************************************************
 *  Front: Returns the item currently at the front of the deque
 *************************************************************/
 template <class T>
 T Deque<T>::front() throw (const char*)
 {
     if(this->empty())
     {
        throw"ERROR: unable to access data from an empty deque";
     }
     if(input)
       return data[frontNum];
     else
     {
        int num = backNum - numItems;
        return data[num];
        }
 }

 /**************************************************************
  *  Back: Returns the item currently at the back of the deque
  *************************************************************/
 template <class T>
 T Deque<T>::back() throw (const char*)
 {
       if(this->empty())
       {
          throw"ERROR: unable to access data from an empty deque";
       }

       //    if the capacity is full
       if (backNum == 0)
          return data[capac -1];
       else
          return data[(backNum-1)%capac];
}

#endif // DEQUE_H
