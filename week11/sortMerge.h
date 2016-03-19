/***********************************************************************
 * Module:
 *    Week 11, Sort Merge
 *    Brother Helfrich, CS 235
 * Author:
 *    Justin Waite & Winson So
 * Summary:
 *    This program will implement the Merge Sort
 ************************************************************************/

#ifndef SORT_MERGE_H
#define SORT_MERGE_H

//template <class T>
//void merge(T arrayL[], T arrayR[], T arrayA[])
//{
//  int num = sizeof(arrayA) / sizeof(arrayA[0]);
//  int numL = num / 2;
//  int numR = num - numL;
//  int iL =0; int iR = 0; int iA = 0;
//
//  while(iL < numL && iR < numR)
//  {
//    if(arrayL[iL] == arrayR[iR] || arrayR[iR] > arrayL[iL])
//    {
//      arrayA[iA] = arrayL[iL];
//      iL++;
//    }
//    else
//    {
//      arrayA[iA] = arrayR[iR];
//      iR++;
//    }
//    iA++;
//  }
//  while(numL > iL)
//  {
//    arrayA[iA] = arrayL[iL];
//    iL++;
//    iA++;
//  }
//  while(numR > iR)
//  {
//    arrayA[iA] = arrayR[iR];
//    iR++;
//    iA++;
//  }
//}

/*****************************************************
 * SORT MERGE
 * Perform the merge sort
 ****************************************************/
template <class T>
void sortMerge(T array[], int num)
{

//  if(num < 2) return;
//  int midF = num / 2;
//  int midB = num - midF;
//  T* arrayL=new T [midF];
//  T* arrayR=new T [midB];
////  T arrayL[midF];
//  // T arrayR[50];
//  //   cout << "HIII :"<<midF<<" "<<midB<<endl;
//
//  for(int i = 0; i < midF; i++)
//  {
//    arrayL[i] = array[i];
//  }
//  for(int i = midF; i < num; i++)
//  {
//    arrayR[i - midF] = array[i];
//  }
//
//  sortMerge(arrayL,midF);
//  sortMerge(arrayR,midB);
//  merge(arrayL,arrayR,array);
//

 }


#endif // SORT_MERGE_H
