/***********************************************************************
 * Module:
 *    Week 11, Sort Heap
 *    Brother Helfrich, CS 235
 * Author:
 *    Justin Waite & Winson So
 * Summary:
 *    This program will implement the Heap Sort
 ************************************************************************/

#ifndef SORT_HEAP_H
#define SORT_HEAP_H

#include "heap.h"

/*****************************************************
 * SORT HEAP
 * Perform the heap sort
 ****************************************************/
template<class T>
void sortHeap(T array[], int num)
{
   Heap<T> heap = Heap<T>(array, num);
   heap.heapify();
   heap.sort();
}


#endif // SORT_HEAP_H
