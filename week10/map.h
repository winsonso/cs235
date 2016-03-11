/***********************************************************************
* Component:
*    Week 10, Map
*    Brother Helfrich, CS 235
* Author:
*    Justin Waite & Winson So
* Summary:
*    This file contains the class definitions for a Map class that works
*    with any data type for the key value and data value and its iterator.
************************************************************************/
#ifndef MAP_H
#define MAP_H

#include <iostream>
#include "bst.h"
#include "pair.h"

using namespace std;

// stub definition for MapIterator
template<class K, class V>
class MapIterator;

/*****************
 * MAP CLASS
 *****************/
template<class K, class V>
class Map
{
public:
   // default constructor
   Map() : numItems(0) { }

   // copy constructor
   Map(const Map<K, V> &rhs) { }

   // destructor
   ~Map() { root.clear(); }

   Map &operator=(Map &rhs);

   // Determines whether the current map is empty
   bool empty() { return root.empty(); }

   // Returns the number of elements currently in the map
   int size() { return numItems; }

   // Delete all the elements in the map
   void clear()
   {
      root.clear();
      numItems = 0;
   }

   // index operator
   V &operator[](const K &key);

   // returns iterator for the first item
   MapIterator<K, V> begin() const
   {
      return MapIterator<K, V>(root.begin());
   }

   // returns iterator for the first item
   MapIterator<K, V> end() const
   {
      return MapIterator<K, V>(root.end());
   }

   // returns iterator for the first item
   MapIterator<K, V> rbegin() const
   {
      return MapIterator<K, V>(root.rbegin());
   }

   // returns iterator for the first item
   MapIterator<K, V> rend() const
   {
      return MapIterator<K, V>(root.rend());
   }

private:
   BST<Pair<K, V> > root;
   int numItems;
};

/***********************
 * CLASS MAP ITERATOR
 ***********************/
template<class K, class V>
class MapIterator
{
public:
   // default constructor
   MapIterator() { }

   // point to a bst iterator
   MapIterator(const BSTIterator<Pair<K, V> > &it) : it(it) { }

   // copy constructor
   MapIterator(const MapIterator &rhs) : it(rhs.it) { }

   // assignment operator
   MapIterator &operator=(const MapIterator &rhs)
   {
      this->it = rhs.it;
      return *this;
   }

   // double equals operator
   bool operator==(const MapIterator &rhs) const
   {
      return rhs.it == this->it;
   }

   // not equals operator
   bool operator!=(const MapIterator &rhs) const
   {
      return (rhs.it != this->it);
   }

   // dereference operator
   V &operator*()
   {
     return (*it).second;
   }

   // prefix increment
   MapIterator &operator++()
   {
      ++it;
      return *this;
   }

   // prefix decrement
   MapIterator &operator--()
   {
      --it;
      return *this;
   }

   // postfix increment
   MapIterator operator++(int postfix)
   {
      MapIterator tmp(*this);
      ++it;
      return tmp;
   }

   // postfix decrement
   MapIterator operator--(int postfix)
   {
      MapIterator tmp(*this);
      --it;
      return tmp;
   }

private:
   BSTIterator<Pair<K, V> > it;
};

/*******************************************
* MAP :: ASSIGNMENT OPERATOR
*******************************************/
template<class K, class V>
Map<K, V> &Map<K, V>::operator=(Map &rhs)
{
   this->root = rhs.root;
   this->numItems = rhs.numItems;

   return *this;
}

/*****************
* Index operator
*****************/
template<class K, class V>
V &Map<K, V>::operator[](const K &key)
{
   BSTIterator<Pair<K, V> > it = root.find(Pair<K, V>(key, V()));

   // if it is not found, insert a new pair and return the reference of value.
   if (it == root.end())
   {
      Pair<K, V> newPair = Pair<K, V>(key, V());
      root.insert(newPair);
      numItems++;
      return (*root.find(newPair)).second;
   }

   // if it is found, return the reference of value.
   return (*it).second;
}


#endif // MAP_H
