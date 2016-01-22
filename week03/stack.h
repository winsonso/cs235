/***********************************************************************
* Header:
*    Stack
* Summary:
*    This class contains the the Stack ADT. A stack holds a list of any
*    data type and has different methods for modifying the list. One can
*    remove an item from the end of stack (pop), add an item to the
*    container (push), return the item currently at the end of the
*    stack (top) and etc.
*
*    This will contain the class definition of:
*        Stack         : A class that holds a collection of data
* Author
*    Justin Waite & Winson So
************************************************************************/

#ifndef STACK_H
#define STACK_H

#include <cassert>
/************************************************
 * STACK
 * A container that holds data in a "stack"
 * pattern. The data can only be accessed from
 * the top of the stack. Last in, first out.
 ***********************************************/
template <class T>
class Stack
{
public:
   // default constructor
   Stack() : numItems(0), capac(0), data(0x00000000) { }

   // copy constructor : copy the stack class
   Stack(const Stack & rhs) throw (const char*);

   // non-default constructor : pre-allocate
   Stack(int capac) throw (const char*);

   // destructor : free everything
   ~Stack()
   {
      if (capac > 0)
         delete [] data;
   }

   // is the stack currently empty
   bool empty() const  { return numItems == 0; }

   // how many items are currently in the stack?
   int size() const    { return numItems;      }

   // push an item onto the stack
   void push(const T &t) throw (const char*);

   // pop the top item off the stack
   void pop() throw (const char*);

   // return the top item on the stack
   T& top() const throw (const char*);

   // assignment operator
   Stack<T>& operator = (const Stack<T> &rhs);

private:
   T* data;           // dynamically allocated array of T
   int numItems;      // how many items are currently in the Container?
   int capac;         // how many items can I put on the Container before full?

   void resize(int newCapac);
};

/**********************************************
 * STACK : RESIZE
 * Attempts to resize the data array to
 * newCapac. Will not downsize, only upsize.
 **********************************************/
template <class T>
void Stack<T> :: resize(int newCapac)
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
      throw "ERROR: Unable to allocate buffer";
   }
}

/*******************************************
 * STACK :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Stack <T> :: Stack(const Stack <T> & rhs) throw (const char *)
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
 * STACK : NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Stack<T> :: Stack(int capac) throw (const char *)
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

   // Set number of items to zero
   this->numItems = 0;

   // initialize the container by calling the default constructor for each item
   for (int i = 0; i < capac; i++)
      data[i] = T();
}

/**********************************************
 * STACK : ASSIGNMENT OPERATOR
 * Sets the stack to a new copy of the rhs.
 **********************************************/
template <class T>
Stack<T>& Stack<T> :: operator = (const Stack<T> &rhs)
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
 *  push: Adds an item to the top of the stack
 ********************************************/
template <class T>
void Stack<T> :: push(const T &t) throw (const char*)
{
   if(capac == 0 )
   {
      capac = 1;
      data = new T[capac];
   }
   else if (capac <= numItems + 1)
   {
      resize(capac * 2);
   }
   data[numItems] = t ;
   numItems++;
}

/*********************************************
 *  Pop: Removes an item from the top of the
 *  stack, serving to reduce the size by one.
 *********************************************/
template <class T>
void Stack<T> :: pop() throw (const char*)
{
   try
   {
      if(this->empty())
      {
         throw "ERROR: Unable to pop from an empty Stack";
      }
      else
         numItems--;
   }
   catch(char* message)
   {
      std::cout << message << std::endl;
   }
}

/*********************************************
 *  Top: Returns the item currently at the top
 *  of the stack.
 *********************************************/
template <class T>
T& Stack<T> :: top() const throw (const char*)
{
   try
   {
      if(this->empty())
      {
         throw "ERROR: Unable to reference the element from an empty Stack";
      }
      return data[numItems - 1];
   }
   catch(char* message)
   {
      std::cout << message << std::endl;
   }
}

#endif // STACK_H
