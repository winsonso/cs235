/***********************************************************************
 * Module:
 *    Week 11, Heap
 *    Brother Helfrich, CS 235
 * Author:
 *    Justin Waite & Winson So
 * Summary:
 *    This file is the definition for the Heap class, a class which
 *    implements the notion of a heap, where any given node is greater
 *    than its child nodes.
 ************************************************************************/

#include <new>

#ifndef WEEK11_HEAP_H
#define WEEK11_HEAP_H

/*****************************************************
 * CLASS HEAP
 * A class which implements the notion of a heap, where
 * any given node is greater than its child nodes.
 ****************************************************/
template<class T>
class Heap
{
public:
   // Default constructor
   Heap() : data(0x00000000), numItems(0) { }

   // Sets data to the given array, does not copy the data so the array
   // can easily be sorted.
   Heap(T array[], int numItems) : data(array), numItems(numItems) { }

   // returns the max data.
   T &getMax() const;

   // deletes the max data and fixes the heap.
   T &deleteMax();

   // percolates down from the index to heapify that sub tree.
   void percolateDown(int index);

   // turns the array into a valid heap.
   void heapify();

   // turns the heap into a sorted array.
   void sort();

private:
   T *data;
   int numItems;
};

#endif //WEEK11_HEAP_H

/*****************************************************
 * HEAP :: GET MAX
 * returns the max data.
 ****************************************************/
template<class T>
T &Heap<T>::getMax() const
{
   if (numItems > 0)
      return data[0];
   return T();
}

/*****************************************************
 * HEAP :: DELETE MAX
 * deletes the max data and fixes the heap.
 ****************************************************/
template<class T>
T &Heap<T>::deleteMax()
{
   if (numItems <= 0)
      return T();

   numItems--;
   data[0] = data[numItems - 1];
   delete data[numItems - 1];

   if (numItems == 0)
      return T();

   percolateDown(1);

   return data[0];
}

/*****************************************************
 * HEAP :: PERCOLATE DOWN
 * percolates down from the index to heapify that sub
 * tree.
 ****************************************************/
template<class T>
void Heap<T>::percolateDown(int index)
{
   int iChild = index * 2;
   while (index <= numItems && iChild <= numItems)
   {
      // check if left or right is bigger, if right set iChild to the right
      // index.
      if (iChild < numItems && data[iChild] > data[iChild - 1])
         iChild++;

      // swap node and largest child if necessary and move down to next subtree
      if (data[iChild - 1] > data[index - 1])
      {
         T temp = data[index - 1];
         data[index - 1] = data[iChild - 1];
         data[iChild - 1] = temp;

         index = iChild;
         iChild *= 2;

      } else
         return;
   }
}

/*****************************************************
 * HEAP :: HEAPIFY
 * turns the array into a valid heap.
 ****************************************************/
template<class T>
void Heap<T>::heapify()
{
   for (int i = numItems / 2; i >= 1; i--)
      percolateDown(i);
}

/*****************************************************
 * HEAP :: SORT
 * turns the heap into a sorted array.
 ****************************************************/
template<class T>
void Heap<T>::sort()
{
   int tempNumItems = numItems;
   for (int i = numItems; i >= 2; i--)
   {
      T temp = data[0];
      data[0] = data[i - 1];
      data[i - 1] = temp;

      // Prune the last leaf
      numItems--;

      percolateDown(1);
   }

   numItems = tempNumItems;
}
