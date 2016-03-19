/***********************************************************************
 * Module:
 *    Week 11, Sort Select
 *    Brother Helfrich, CS 235
 * Author:
 *    Justin Waite & Winson So
 * Summary:
 *    This program will implement the Selection Sort
 ************************************************************************/

#ifndef SORT_SELECTION_H
#define SORT_SELECTION_H

/***************************************
 * SORT SELECTION
 * Find the smallest value then
 * swap it to the front
 ***************************************/
template<class T>
void sortSelection(T array[], int num)
{
   for (int i = 0; i < num - 1; i++)
   {
      int min = i;
      for (int j = i + 1; j < num; j++)
      {
         if (array[min] > array[j])
            min = j;
      }
      T tmp = array[min];
      array[min] = array[i];
      array[i] = tmp;
   }
}


#endif // SORT_SELECTION_H
