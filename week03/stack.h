/***********************************************************************
* Header:
*    Stack
* Summary:
*    This class is a stack container, which holds data in a "last in,
*    first out" pattern. Data can only be accessed from the top of the
*    stack.
*
*    This will contain the class definition of:
*        Stack         : A container holding data in a "stack" pattern.
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
      if (capac)
         delete[] data;
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


private:
   T* data;           // dynamically allocated array of T
   int numItems;      // how many items are currently in the Container?
   int capac;         // how many items can I put on the Container before full?
};
/*******************************************
 * STACK :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Stack <T> :: Stack(const Stack <T> & rhs) throw (const char *)
{
   assert(rhs.capac >= 0);

   // do nothing if there is nothing to do
   if (rhs.capac == 0)
   {
      capac = numItems = 0;
      data = 0x00000000;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.capac];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

   // copy over the capacity and size
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.capac);
   capac = rhs.capac;
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

   // do nothing if there is nothing to do
   if (capac == 0)
   {
      this->capac = this->numItems = 0;
      this->data = 0x00000000;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[capac];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

   // copy over the capacity and number of items
   this->capac = capac;
   this->numItems = 0;

   // initialize the container by calling the default constructor for each item
   for (int i = 0; i < capac; i++)
      data[i] = T();
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
      capac = capac * 2;
      try
      {
         //allocate the array
         T* temp = data;
         data = new T[capac];
         for(int i = 0; i < numItems; i++)
            data[i] = temp[i];
         delete[] temp;
      }
      catch (std::bad_alloc)
      {
         throw "Unable to allocate a new buffer for Stack";
      }
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

#endif // CONTAINER_H
