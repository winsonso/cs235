/***********************************************************************
 * Implementation:
 *    FIBONACCI
 * Summary:
 *    This will contain the implementation for fibonacci() as well as any
 *    other function or class implementations you may need
 * Author
 *    Justin Waite & Winson So
 **********************************************************************/

#include <iostream>
#include "fibonacci.h"   // for fibonacci() prototype
#include "list.h"        // for LIST
#include "wholenumber.h" // for WholeNumber
using namespace std;


/************************************************
 * FIBONACCI
 * The interactive function allowing the user to
 * display Fibonacci numbers
 ***********************************************/
void fibonacci()
{
   // show the first serveral Fibonacci numbers
   int number;
   cout << "How many Fibonacci numbers would you like to see? ";
   cin  >> number;

   int y = 0;
   int x = 1;
   int temp;

   for (int i = 0; i < number; i++)
   {
      temp = y;
	   y = x;
	   x = x + temp;
      cout << '\t' << y << endl;
	}

   // your code to display the first <number> Fibonacci numbers

   // prompt for a single large Fibonacci
   cout << "Which Fibonacci number would you like to display? ";
   cin  >> number;

   WholeNumber wy = WholeNumber(0);
   WholeNumber wx = WholeNumber(1);
   WholeNumber wTemp = WholeNumber(0);

   for (int i = 0; i < number; i++)
   {
      wTemp = wy;
	   wy = wx;
	   wx += wTemp;
	}
   cout << '\t' << wy << endl;
}
