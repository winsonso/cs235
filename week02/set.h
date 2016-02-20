/***********************************************************************
 * Header:
 *    Set Container
 * Summary:
 *    This class contains the Set ADT. A set holds a list of any data
 *    type and has different methods for modifying the list. One can
 *    insert a new item, find an item, delete an item, clear all the
 *    contents, etc.
 *
 *    This will contain the class definition of:
 *        Set         : A class that holds a collection of data
 *        SetIterator : An interator through Set
 *        SetConstIterator : An const interator through Set
 * Author
 *    Justin Waite & Winson So
 ************************************************************************/

#ifndef SET_H
#define SET_H

#include <cassert>

// Forward declaration for SetIterator
template <class T>
class SetIterator;
template <class T>
class SetConstIterator;

/************************************************
 * SET CLASS
 * A class that is used to hold and modify a list
 * of data.
 ***********************************************/
template <class T>
class Set
{
private:

   T  *data;     // dynamically allocated array of T
   int numItems; // how many items are currently in the Container?
   int capac;    // how many items can I put on the Container before full?

public:

   // default constructor : empty and kinda useless
   Set() : numItems(0), capac(0), data(0x00000000) {}

   // copy constructor : copy it
   Set(const Set &rhs) throw(const char *);

   // non-default constructor : pre-allocate
   Set(int capac) throw(const char *);

   // destructor : free everything
   ~Set()        {
      if (capac)
      {
         delete[] data;
      }
   }

   // increases capacity of the data array by a given amount.
   void increaseCapacity(int incAmount) throw(const char *);

   // is the container currently empty
   bool empty() const  {
      return numItems == 0;
   }

   // remove all the items from the set
   void clear()        {
      numItems = 0;
   }

   // delete an item at the location of the iterator.
   void erase(SetIterator<T> it);

   // how many items are currently in the container?
   int  size() const    {
      return numItems;
   }

   // add an item to the container
   void insert(const T& t) throw(const char *);

   // capacity
   int  capacity() const {
      return capac;
   }

   // return an iterator to the beginning of the list
   SetIterator <T> begin() {
      return SetIterator<T>(data);
   }

   // return an iterator to the end of the list
   SetIterator <T> end() {
      return SetIterator<T>(data + numItems);
   }

   // return a location of iterator
   SetIterator <T> find(const T &t);

   // return an iterator to the beginning of the list
   SetConstIterator <T> cbegin() const { return SetConstIterator<T>(data); }

   // return an iterator to the end of the list
   SetConstIterator <T>
   cend() const { return SetConstIterator<T>(data + numItems); }

   // operator return by reference
   T& operator[] (int index)throw(bool) {
      return data[index];
   }

   // operator return by value
   T operator()(int index) throw(bool) {
      return data[index];
   }

   // Operators
   Set<T>& operator = (const Set<T> &rhs);
   Set<T> operator - (const Set<T> &rhs);
   Set<T> operator || (const Set<T> &rhs);
   Set<T> operator && (const Set<T> &rhs);
};

/**************************************************
 * SET ITERATOR
 * An iterator through Container
 *************************************************/
template <class T>
class SetIterator
{
public:

   // default constructor
   SetIterator() : p(0x00000000) {}

   // initialize to direct p to some item
   SetIterator(T * p) : p(p) {}

   // copy constructor
   SetIterator(const SetIterator &rhs) {
      *this = rhs;
   }


   // assignment operator
   SetIterator& operator = (const SetIterator &rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // not equals operator
   bool operator != (const SetIterator &rhs) const
   {
      return rhs.p != this->p;
   }

   // equals operator
   bool operator = (const SetIterator &rhs) const
   {
      return rhs.p = this->p;
   }

   // eaual operator
   bool operator == (const SetIterator &rhs) const
   {
      return rhs.p == this->p;
   }

   // dereference operator
   T& operator * ()
   {
      return *p;
   }

   // prefix increment
   SetIterator <T> &operator++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   SetIterator <T> operator++ (int postfix)
   {
      SetIterator tmp(*this);
      p++;
      return tmp;
   }

private:

   T *p;
};

/**************************************************
 * SET CONST ITERATOR
 * An iterator through Container
 *************************************************/
template <class T>
class SetConstIterator
{
public:

   // default constructor
   SetConstIterator() : p(0x00000000) {}

   // initialize to direct p to some item
   SetConstIterator(T * p) : p(p) {}

   // copy constructor
   SetConstIterator(const SetConstIterator &rhs) {
      *this = rhs;
   }


   // assignment operator
   SetConstIterator& operator = (const SetConstIterator &rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // not equals operator
   bool operator != (const SetConstIterator &rhs) const
   {
      return rhs.p != this->p;
   }

   // equals operator
   bool operator = (const SetConstIterator &rhs) const
   {
      return rhs.p = this->p;
   }

   // eaual operator
   bool operator == (const SetConstIterator &rhs) const
   {
      return rhs.p == this->p;
   }

   // dereference operator
   T& operator * ()
   {
      return *p;
   }

   // prefix increment
   const SetConstIterator <T>& operator++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   const SetConstIterator <T> operator++ (int postfix)
   {
      SetConstIterator tmp(*this);
      p++;
      return tmp;
   }

   // postfix decrement
   const SetConstIterator <T>& operator-- ()
   {
      p--;
      return *this;
   }

   // Postfix decrement operator.
   const SetConstIterator <T> operator-- (int postfix)
   {
      SetConstIterator tmp(*this);
      p--;
      return tmp;
   }

private:

   T *p;
};

/*******************************************
* SET :: COPY CONSTRUCTOR
*******************************************/
template <class T>
Set <T> ::Set(const Set <T> &rhs) throw(const char *)
{
   assert(rhs.capac >= 0);

   // do nothing if there is nothing to do
   if (rhs.capac == 0)
   {
      capac = numItems = 0;
      data  = 0x00000000;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.capac];
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }


   // copy over the capacity and size
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.capac);
   capac    = rhs.capac;
   numItems = rhs.numItems;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numItems; i++)
   {
      data[i] = rhs.data[i];
   }
}

/**********************************************
* SET : NON-DEFAULT CONSTRUCTOR
* Preallocate the container to "capacity"
**********************************************/
template <class T>
Set <T> ::Set(int capac) throw(const char *)
{
   assert(capac >= 0);

   // do nothing if there is nothing to do
   if (capac == 0)
   {
      this->capac = this->numItems = 0;
      this->data  = 0x00000000;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[capac];
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

   // copy over the stuff
   this->capac    = capac;
   this->numItems = 0;

   // initialize the container by calling the default constructor
   for (int i = 0; i < capac; i++)
   {
      data[i] = T();
   }
}

/***************************************************
 * SET :: INSERT
 * Insert an item on the end of the list
 **************************************************/
template <class T>
void Set<T>::insert(const T &t) throw(const char *)
{
   // check if there is anything in the set
   if (numItems == 0)
   {
      if (capac == 0)
      {
         capac = 1;
         data  = new T[capac];
      }
      numItems++;
      data[0] = t;
      return;
   }

   // check the capacity
   if (capac <= numItems)
   {
      increaseCapacity(capac);
   }

   // check the data if it is existed and insert
   int i;

   for (i = 0; i < numItems; i++)
   {
      if (data[i] == t)
      {
         return;
      }

      if (data[i] > t)
      {
         break;
      }
   }

   for (int n = numItems; n > i; n--)
   {
      data[n] = data[n - 1];
   }

   data[i] = t;
   numItems++;
}

/*********************
 * Assign operators =
 **********************/
template <class T>
Set<T>& Set<T>::operator = (const Set<T> &rhs)
{
   if (this == &rhs)
   {
      return *this;
   }

   if (rhs.numItems > capac)
   {
      increaseCapacity(rhs.numItems - capac);
   }

   numItems = rhs.numItems;

   for (int i = 0; i < numItems; i++)
   {
      data[i] = rhs.data[i];
   }

   return *this;
}

/*******************
* Opertaors ||
*******************/
template <class T>
Set<T> Set<T>::operator || (const Set<T> &rhs)
{
   Set tem;

   for (int i = 0; i < numItems; i++)
   {
      tem.insert(data[i]);
   }

   for (int k = 0; k < rhs.numItems; k++)
   {
      tem.insert(rhs.data[k]);
   }

   return tem;
}

/**********************
 * Operators &&
 ***********************/
template <class T>
Set<T> Set<T>::operator && (const Set<T> &rhs)
{
   // so we can replace a clean set, this is just temperory to save my intems
   // that are the same
   Set temp;

   for (int i = 0; i < numItems; i++)
   {
      for (int k = 0; k < rhs.numItems; k++)
      {
         if (data[i] == rhs.data[k])
         {
            temp.insert(data[i]);
         }
      }
   }
   return temp;
}

/**********************
 * Operators &&
 ***********************/
template <class T>
Set<T> Set<T>::operator - (const Set<T> &rhs)
{
   Set temp;

   //       try
   //    {
   //       data = new T[capac];
   //    }
   //    catch (std::bad_alloc)
   //    {
   //       throw "ERROR: Unable to allocate buffer";
   //    }
   //       for(int i = 0; i < numItems; i++)
   //    {
   //       temp.data[i] = data[i] - rhs.data[i];
   //    }

   temp.numItems = numItems - rhs.numItems;
   temp.capac    = capac - rhs.capac;
   return temp;
}

/***************************************************
* Set :: increaseCapacity
* Increases the capacity of the data array
***************************************************/
template <class T>
void Set <T> ::increaseCapacity(int incAmount) throw(const char *)
{
   T *dataBuffer;

   // Attempt to allocate new buffer array
   try
   {
      dataBuffer = new T[capac + incAmount];
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

   // change the m_capacity variable
   capac += incAmount;

   // fill the dataBuffer with current data
   for (int i = 0; i < numItems; i++)
   {
      dataBuffer[i] = data[i];
   }

   if (capac != incAmount)
   {
      delete[] data;
   }

   data = dataBuffer;
}

/*************************
 * Find Function
 ****************************/
template <class T>
SetIterator<T>Set<T>::find(const T &t)
{
   for (int i = 0; i <numItems; i++)
   {
      if (data[i] == t)
      {
         return SetIterator<T>(data + i);
      }
   }
   return this->end();
}

/****************************
 * Erase Function
 *****************************/
template <class T>
void Set<T>::erase(SetIterator<T> it)
{
   int k;

   for (int i = 0; i < numItems; i++)
   {
      if (data[i] == *it)
      {
         k = i;
         break;
      }
   }

   for (int a = k; a <numItems - 1; a++)
   {
      data[a] = data[a + 1];
   }
   numItems--;
}
 #endif // CONTAINER_H
