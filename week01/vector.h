/***********************************************************************
* Header:
*    Vector
* Summary:
*    This class contains the notion of a Vector: a bucket to hold
*    data for the user. This is just a starting-point for more advanced
*    constainers such as the vector, set, stack, queue, deque, and map
*    which we will build later this semester.
*
*    This will contain the class definition of:
*        Vector         : A class that holds stuff
*        VectorIterator : An interator through Vector
* Author
*    Br. Helfrich, modified by Justin Waite 
************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>

// forward declaration for VectorIterator
template <class T>
class VectorIterator;

/************************************************
 * Vector
 * A class that holds stuff
 ***********************************************/
template <class T>
class Vector
{
public:
   // default constructor : empty and kinda useless
   Vector() : numItems(0), m_capacity(0), data(0x00000000) {}

   // copy constructor : copy it
   Vector(const Vector & rhs) throw (const char *);

   // non-default constructor : pre-allocate
   Vector(int m_capacity) throw (const char *);

   // destructor : free everything
   ~Vector()        { if (m_capacity) delete [] data; }

   // is the Vector currently empty
   bool empty() const   { return numItems == 0;         }

   // remove all the items from the Vector
   void clear()         { numItems = 0;                 }

   // how many items are currently in the Vector?
   int size() const     { return numItems;              }

   // return the capacity of the Vector
   int capacity() const { return m_capacity;            }

   // add an item to the Vector
   void push_back(const T & t) throw (const char *);

   T& operator[](int index) throw (const char *);

   Vector<T>& operator=(Vector <T> & rhs) throw (const char *);

   T operator()(int index) throw (const char *);

   // return an iterator to the beginning of the list
   VectorIterator <T> begin() { return VectorIterator<T>(data); }

   // return an iterator to the end of the list
   VectorIterator <T> end() { return VectorIterator<T>(data + numItems);}

private:
   T * data;          // dynamically allocated array of T
   int numItems;      // how many items are currently in the Vector?
   int m_capacity;      // how many items can I put on the Vector before full?

   //Attempt to increase the capacity by the given amount
   void increaseCapacity(int incAmount) throw (const char *);

   //Check if a given index is in range
   bool inRange(int index) const { return index >= 0 && index <= numItems - 1; }
};

/**************************************************
 * Vector ITERATOR
 * An iterator through Vector
 *************************************************/
template <class T>
class VectorIterator
{
  public:
   // default constructor
  VectorIterator() : p(0x00000000) {}

   // initialize to direct p to some item
  VectorIterator(T * p) : p(p) {}

   // copy constructor
   VectorIterator(const VectorIterator & rhs) { *this = rhs; }

   // assignment operator
   VectorIterator & operator = (const VectorIterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // not equals operator
   bool operator != (const VectorIterator & rhs) const
   {
      return rhs.p != this->p;
   }

   // dereference operator
   T & operator * ()
   {
      return *p;
   }

   // prefix increment
   VectorIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   VectorIterator <T> operator++(int postfix)
   {
      VectorIterator tmp(*this);
      p++;
      return tmp;
   }

  private:
   T * p;
};

/*******************************************
 * Vector :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Vector <T> :: Vector(const Vector <T> & rhs) throw (const char *)
{
   assert(rhs.m_capacity >= 0);

   // do nothing if there is nothing to do
   if (rhs.m_capacity == 0)
   {
      m_capacity = numItems = 0;
      data = 0x00000000;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.m_capacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

   // copy over the capacity and size
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.m_capacity);
   m_capacity = rhs.m_capacity;
   numItems = rhs.numItems;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numItems; i++)
      data[i] = rhs.data[i];

   // the rest needs to be filled with the default value for T
   for (int i = numItems; i < m_capacity; i++)
      data[i] = T();
}

/**********************************************
 * Vector : NON-DEFAULT CONSTRUCTOR
 * Preallocate the Vector to "capacity"
 **********************************************/
template <class T>
Vector <T> :: Vector(int m_capacity) throw (const char *)
{
   assert(m_capacity >= 0);

   // do nothing if there is nothing to do
   if (m_capacity == 0)
   {
      this->m_capacity = this->numItems = 0;
      this->data = 0x00000000;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[m_capacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }


   // copy over the stuff
   this->m_capacity = m_capacity;
   this->numItems = 0;

   // initialize the Vector by calling the default constructor
   for (int i = 0; i < m_capacity; i++)
      data[i] = T();
}

/*******************************************
 * Vector :: ASSIGNMENT OPERATOR
 *******************************************/
template <class T>
Vector<T>& Vector <T> :: operator=(Vector<T> & rhs) throw (const char *)
{
   assert(rhs.m_capacity >= 0);

   // do nothing if there is nothing to do
   if (rhs.m_capacity == 0)
   {
      this->m_capacity = numItems = 0;
      this->data = 0x00000000;
      return *this;
   }

   // attempt to allocate
   try
   {
      this->data = new T[rhs.m_capacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

   // copy over the capacity and size
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.m_capacity);
   this->m_capacity = rhs.m_capacity;
   this->numItems = rhs.numItems;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numItems; i++)
      this->data[i] = rhs.data[i];

   // the rest needs to be filled with the default value for T
   for (int i = numItems; i < m_capacity; i++)
      this->data[i] = T();

   return *this;
}

/***************************************************
 * Vector :: increaseCapacity
 * Increases the capacity of the data array
 **************************************************/
template <class T>
void Vector <T> :: increaseCapacity(int incAmount) throw (const char *)
{
  T * dataBuffer;

  //Attempt to allocate new buffer array
  try
  {
     dataBuffer = new T[m_capacity + incAmount];
  }
  catch (std::bad_alloc)
  {
     throw "ERROR: Unable to allocate buffer";
  }

  // change the m_capacity variable
  m_capacity = m_capacity + incAmount;

  // fill the dataBuffer with current data
  for (int i = 0; i < numItems; i++)
     dataBuffer[i] = data[i];
  delete [] data;
  data = dataBuffer;
}

/***************************************************
 * Vector :: PUSH_BACK
 * Insert an item on the end of the Vector
 **************************************************/
template <class T>
void Vector <T> :: push_back(const T & t) throw (const char *)
{
   // if no capacity is set, let's add 1.
   if (m_capacity == 0)
   {
     increaseCapacity(1);
   }
   // if the capacity limit has been reached, double the capacity!
   else if (m_capacity == numItems)
   {
     increaseCapacity(m_capacity);
   }


   // add an item to the end
   data[numItems++] = t;
}

template <class T>
T& Vector <T> :: operator[](int index) throw (const char *)
{
  if (!inRange(index))
  {
    throw "ERROR: Invalid index";
  }

  return data[index];
}

template <class T>
T Vector <T> :: operator()(int index) throw (const char *) {
  if (!inRange(index))
  {
    throw "ERROR: Invalid index";
  }

  return data[index];
}

#endif // Vector_H
