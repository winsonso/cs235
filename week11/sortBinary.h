/***********************************************************************
 * Module:
 *    Week 11, Sort Binary
 *    Brother Helfrich, CS 235
 * Author:
 *    Justin Waite & Winson So
 * Summary:
 *    This program will implement the Binary Tree Sort
 ************************************************************************/

#ifndef SORT_BINARY_H
#define SORT_BINARY_H

#include "bst.h"
#include <cassert>

/*****************************************************
 * SORT BINARY
 * Perform the binary tree sort
 ****************************************************/
template<class T>
void sortBinary(T array[], int num)
{
   // Fill the array
   BST<T> bst;

   for (int i = 0; i < num; i++)
      bst.insert(array[i]);

   int currIndex = 0;
   for (BSTIterator<T> it = bst.begin(); it != bst.end(); ++it)
      array[currIndex++] = *it;
}


#endif // SORT_BINARY_H
