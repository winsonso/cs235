/***********************************************************************
* Header:
*    Stack Container
* Summary:
*    This class contains the notion of a container: a bucket to hold
*    data for the user. This is just a starting-point for more advanced
*    constainers such as the vector, set, stack, queue, deque, and map
*    which we will build later this semester.
*
*    This will contain the class definition of:
*        Container         : A class that holds stuff
*        ContainerIterator : An interator through Container
* Author
*    Br. Helfrich
************************************************************************/

#ifndef STACK_H
#define STACK_H

#include <cassert> 
/************************************************
 * STACK
 * A class that holds stuff
 ***********************************************/
template <class T>
class Stack
{
public:
   // default constructor : empty and kinda useless
   Stack() : numItems(0), capac(0), data(0x00000000) {}

   // copy constructor : copy it
   Stack(const Stack & rhs) throw (const char *);
   
   // non-default constructor : pre-allocate
   Stack(int capac) throw (const char *);
   
   // destructor : free everything
   ~Stack()            {numItems = 0; }
   // is the container currently empty
   bool empty() const  { return numItems == 0;         }

   // how many items are currently in the container?
   int size() const    { return numItems;              }

   // capacity
   int capacity() const {return capac;}
   
   // push
   void push(const T &t) throw (const char*);

   // pop
   void pop() throw (const char*);

   // top
   T top() throw (const char*);
   
      
private:
   T * data;          // dynamically allocated array of T
   int numItems;      // how many items are currently in the Container?
   int capac;      // how many items can I put on the Container before full?
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
Stack <T> :: Stack(int capac) throw (const char *)
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
   // copy over the stuff
   this->capac = capac;
   this->numItems = 0;

   // initialize the container by calling the default constructor
   for (int i = 0; i < capac; i++)
      data[i] = T();
}
/****************************************
 *  push: Adds an item to the container.
 ****************************************/
template <class T>
void Stack<T>::push(const T &t) throw (const char*)
{
   if(capac == 0 )
   {
      capac = 1;
      data = new T[capac];
   }
   else if (capac <= numItems+1)
   {
      capac = capac*2;
    try
   {
      //allocate the array
      T*temp = data; 
      data = new T[capac];
      for(int i = 0; i < numItems ; i++)
         data[i] = temp[i];
      delete[] temp;
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   }
   data[numItems] = t ;
   numItems++;
   
}
/********************************
 *  Pop: Removes an item from the
 *       end of the stack, serving
 *       to reduce the size by one.
 ********************************/
template <class T>
void Stack<T>::pop() throw (const char*)
{
try
 {
    if(this->empty())
    {
       throw"ERROR: Unable to pop from an empty Stack";
    }
    else
    numItems--;
 }
 catch(char *message)
 {
    std::cout << message;
 }
   
}

/*********************************
 *  Top: Returns the item currently
 *       at the end of the stack.
 *********************************/
template <class T>
T Stack<T>::top() throw (const char*)
{
 try
 {
    if(this->empty())
    {
       throw"ERROR: Unable to reference the element from an empty Stack";
    }
    return data[numItems -1];
 }
 catch(char *message)
 {
    std::cout << message;
 }
}
#endif // CONTAINER_H
