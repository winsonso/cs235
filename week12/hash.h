/***********************************************************************
 * Header:
 *    HASH
 * Author:
 *    Justin Waite & Winson So
 * Summary:
 *    This file contains the class will store a collection of elements
 *    and be able to perform constant-time insertion and lookup.
 ************************************************************************/
#ifndef WEEK12_HASH_H
#define WEEK12_HASH_H

#include "list.h"
#include <iostream>

using namespace std;

/***********************
 * HASH CLASS
 * Hash class definition
 ***********************/
template<class T>
class Hash
{
public:
   // non-default constructor
   Hash(int buckets) throw (const char*);

   // copy constructor
   Hash(const Hash<T> &rhs);

   // assignment operator
   Hash<T> &operator=(const Hash<T> &rhs);

   // determine if hash is empty;
   bool empty() const { return numItems == 0; }

   // return the number of items in the hash
   int size() const { return numItems; }

   // return the number of buckets for the hash
   int capacity() const { return buckets; }

   // returns true if item is found, false if not.
   bool find(const T &item) const;

   // inserts an item into the hash
   void insert(const T &item);

   virtual int hash(const T & value) const = 0;

private:
   int buckets;
   int numItems;
   List<T> *data;
};

/**************************
 * NON-DEFAULT CONSTRUCTOR
 **************************/
template<class T>
Hash<T>::Hash(int buckets) throw (const char*) : buckets(buckets), numItems(0)
{
   try
   {
      data = new List<T>[buckets];
   }
   catch(std::bad_alloc)
   {
      throw "Unable to allocate array.";
   }
}

/**************************************************
 * COPY CONSTRUCTOR
 * Constructs a new Hash, copying the given one.
 **************************************************/
template<class T>
Hash<T>::Hash(const Hash<T> &rhs)
{
  buckets = rhs.buckets;
  numItems = rhs.numItems;
  data = rhs.data;
}

/********************************
 * ASSIGNMENT OPERATOR
 * Copies one hash into another.
 ********************************/
template<class T>
Hash<T>& Hash<T>::operator=(const Hash<T> &rhs)
{
  buckets = rhs.buckets;
  numItems = rhs.numItems;
  data = rhs.data;
  return *this;
}

/*************************************************
 * FIND
 * Returns true if an item is found in the hash,
 * false if it is not.
 *************************************************/
template<class T>
bool Hash<T>::find(const T &item) const
{
  int index = hash(item);
  for (ListIterator<T> it = data[index].begin();
     it != data[index].end(); ++it)
   if (*it == item)
      return true;
    return false;
}

/*************************************************
 * INSERT
 * Inserts a new instance of a value into the hash.
 *************************************************/
template<class T>
void Hash<T>::insert(const T &item)
{
   int index = hash(item);
   data[index].push_front(item);
   numItems++;
}

#endif //WEEK12_HASH_H
