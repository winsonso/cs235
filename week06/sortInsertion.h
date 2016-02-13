/***********************************************************************
 * Header:
 *    INSERTION SORT
 * Summary:
 *    This will contain just the prototype for insertionSortTest(). You may
 *    want to put other class definitions here as well.
 * Author
 *    Justin Waite & Winson So
 ************************************************************************/

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "node.h"

/***********************************************
 * INSERTION SORT
 * Sort the items in the array
 **********************************************/
template <class T>
void sortInsertion(T array[], int num)
{
   if (num <= 0)
      return;

   Node<T> * pHead = new Node<T>(array[0]);

   for (int i = 1; i < num; i++)
   {
      // If we need to insert to the front
      if (pHead->data > array[i])
      {
         Node<T> * tmp = new Node<T>(array[i]);
         tmp->pNext = pHead;
         pHead = tmp;
      }

      //Otherwise traverse and find where to insert
      else
      {
         for (Node<T> * ptr = pHead; ptr; ptr = ptr->pNext)
         {
            Node<T> * tmp = new Node<T>(array[i]);
            if (ptr->pNext && ptr->pNext->data > array[i])
            {
               tmp->pNext = ptr->pNext;
               ptr->pNext = tmp;
               break;
            }
            else if (!ptr->pNext)
            {
               ptr->pNext = tmp;
               break;
            }
         }
      }
   }

   int i = 0;
   for (Node<T> * ptr = pHead; ptr; ptr = ptr->pNext)
      array[i++] = ptr->data;
}

#endif // INSERTION_SORT_H
