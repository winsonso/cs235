 /***********************************************************************
 * Component:
 *    Week 10, Binary Search Tree (BST)
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

/*****************
 * MAP CLASS
 *****************/
template <class T, class A>
class Map
{
  public:
  // default constructor
  Map(): items(0){}

   // copy constructor
   Map(const Map<T, A> & rhs){}

   // destuctor
   ~Map(){items = 0;}

   // Determines whether the current map is empty
   bool empty(){return (items == 0) ? true : false;}

   // Returns the number of elements currently in the map
   int size() {return items;}

   // Delete all the elements in the map
   void clear() {}

   // index operator
    A & operator [] (const T &key);

  private:
   BST<Pair<T,A> >* bst;
   int items;
};

/*****************
 * Index operator
 *****************/
template <class T, class A>
A & Map<T,A>::operator[] (const T & key)
{


}


/***********************
 * MAPITERATOR CLASS
 ***********************/
template <class T, class A>
class MapIterator
{
public:
   // default constructor
   MapIterator() {}

   // copy constructor
   MapIterator(const BSTIterator< Pair<T,A> > & bst) {}


};


#endif // MAP_H
