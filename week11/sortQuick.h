/***********************************************************************
 * Module:
 *    Week 11, Sort Quick
 *    Brother Helfrich, CS 235
 * Author:
 *    Justin Waite & Winson So
 * Summary:
 *    This program will implement the Quick Sort
 ************************************************************************/

#ifndef SORT_QUICK_H
#define SORT_QUICK_H

// Function stub for the quickSort method.
template<class T>
void quickSort(T *arr, int first, int last);

// Function stub for the split method.
template<class T>
int split(T arr[], int first, int last);

/*****************************************************
 * SORT QUICK
 * Initiates the quick sort method.
 ****************************************************/
template<class T>
void sortQuick(T array[], int num)
{
   if (num <= 1)
      return;

   quickSort(array, 0, num - 1);
}

/*****************************************************
 * QUICK SORT
 * Perform the quick sort
 ****************************************************/
template<class T>
void quickSort(T *arr, int first, int last)
{
   int pos; // pivot's final position
   if (first < last) // list size is > 1
   {
      pos = split(arr, first, last);
      quickSort(arr, first, pos - 1);
      quickSort(arr, pos + 1, last);
   }
   // else list has 0 or 1 elements and requires no sorting.
}

/*****************************************************
 * SPLIT
 * The meat of the quick sort, this function chooses
 * a pivot and arranges the array to put elements <
 * the pivot on the left and > the pivot on the right.
 ****************************************************/
template<class T>
int split(T arr[], int first, int last)
{
   T pivot = arr[first];
   int left = first;
   int right = last;

   while (right > left)
   {
      while (arr[right] > pivot)
         right--;

      while (right > left && (pivot > arr[left] || arr[left] == pivot))
         left++;

      if (right > left)
         swap(arr[left], arr[right]);
   }

   //place pivot in correct position;
   int pos = right;
   arr[first] = arr[pos];
   arr[pos] = pivot;
   return pos;
}

#endif // SORT_QUICK_H
