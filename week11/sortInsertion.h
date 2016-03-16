/***********************************************************************
 * Module:
 *    Week 11, Sort Insertion
 *    Brother Helfrich, CS 235
 * Author:
 *    Winson So & Justin Waite
 * Summary:
 *    This program will implement the Insertion Sort
 ************************************************************************/

#ifndef SORT_INSERTION_H
#define SORT_INSERTION_H

#include <cassert>

/*****************************************************
 * SORT INSERTION
 * Perform the insertion sort
 ****************************************************/
template <class T>
void sortInsertion(T array[], int num)
{
  for (int i = 1; i < num; i++)
  {
    T value = array[i];
    int hole = i;
    while (hole > 0 && array[hole - 1] > value)
    {
      array[hole] = array[hole - 1];
      hole = hole - 1;
    }
    array[hole] = value;
  }
}


#endif // SORT_INSERTION_H
