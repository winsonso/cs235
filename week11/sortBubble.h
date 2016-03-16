/***********************************************************************
 * Module:
 *    Week 11, Sort Bubble
 *    Brother Helfrich, CS 235
 * Author:
 *    Winson So & Justin Waite
 * Summary:
 *    This program will implement the Bubble Sort
 ************************************************************************/

#ifndef SORT_BUBBLE_H
#define SORT_BUBBLE_H

/*****************************************************
 * SORT BUBBLE
 * Compare two by two, the one is larger then swap it
 * to the left
 ****************************************************/
template <class T>
void sortBubble(T array[], int num)
{
  for (int k = 0; k < num - 1; k++)
  {
    for (int i = 0; i < num - k - 1; i++)
    {
      if(array[i] > array[i+1])
      {
        T tmp = array[i+1];
        array[i+1] = array[i];
        array[i] = tmp;
      }
    }
  }
}


#endif // SORT_BUBBLE_H
