/***********************************************************************
* Program:
*    Week 02, Set
*    Brother Helfrich, CS 235
* Author:
*    Br. Helfrich
* Summary: 
*    This is a driver program to exercise the Set class.  When you
*    submit your program, this should not be changed in any way.  That being
*    said, you may need to modify this once or twice to get it to work.
************************************************************************/

#include <iostream>       // for CIN and COUT
#include <string>         // because testIterate() uses a Set of string
#include "set.h"          // your Set class needs to be in set.h
#include "goFish.h"       // your goFish() function needs to be defined here
using namespace std;

// prototypes for our four test functions
void testSimple();
void testFill();
void testFind();
void testUnionIntersection();
void testConstIterator();
void testDifference();

// To get your program to compile, you might need to comment out a few
// of these. The idea is to help you avoid too many compile errors at once.
// I suggest first commenting out all of these tests, then try to use only
// TEST1.  Then, when TEST1 works, try TEST2 and so on.
#define TEST1   // for testSimple()
#define TEST2   // for testFill()
#define TEST3   // for testFind()
#define TEST4   // for testUnionItersection()
#define TEST5   // for testConstIterator()
#define TEST6   // for testDifference()

/**********************************************************************
 * MAIN
 * This is just a simple menu to launch a collection of tests
 ***********************************************************************/
int main()
{
   // menu
   cout << "Select the test you want to run:\n";
   cout << "\t1. Just create and destroy a Set.\n";
   cout << "\t2. The above plus fill and iterate through the Set.\n";
   cout << "\t3. The above plus find if an item is in the Set.\n";
   cout << "\t4. The above plus union and intersection.\n";
   cout << "\t5. Extra credit: test the const iterator.\n";
   cout << "\t6. Extra credit: test the difference operator.\n";
   cout << "\ta. Go Fish!\n";

   // select
   char choice;
   cout << "> ";
   cin  >> choice;
   switch (choice)
   {
      case 'a':
         goFish();
         break;
      case '1':
         testSimple();
         cout << "Test 1 complete\n";
         break;
      case '2':
         testFill();
         cout << "Test 2 complete\n";
         break;
      case '3':
         testFind();
         cout << "Test 3 complete\n";
         break;
      case '4':
         testUnionIntersection();
         cout << "Test 4 complete\n";
         break;
      case '5':
         testConstIterator();
         cout << "Extra credit: const iterator completed\n";
         break;
      case '6':
         testDifference();
         cout << "Extra credit: difference completed\n";
         break;
      default:
         cout << "Unrecognized command, exiting...\n";
   }
   
   return 0;
}

/*******************************************
 * TEST SIMPLE
 * Very simple test for a set: create and destroy
 ******************************************/
void testSimple()
{
#ifdef TEST1
   // Test1: bool Set with default constructor
   cout << "Create a bool Set using default constructor\n";
   Set <bool> s1;
   cout << "\tSize:  " << s1.size() << endl;
   cout << "\tEmpty? " << (s1.empty() ? "Yes" : "No") << endl;

   {
      // Test2: double Set with non-default constructor
      cout << "Create a double Set using the non-default constructor\n";
      Set <double> s2(10 /*capacity*/);
      cout << "\tSize:  " << s2.size() << endl;
      cout << "\tEmpty? " << (s2.empty() ? "Yes" : "No") << endl;
   }
   cout << "\tDestroying the second Set\n";
#endif // TEST1
}

/******************************************
 * TEST FILL
 * This will test the following:
 *   1. Instantiating a Set object
 *   2. Filling the contents with values
 *   3. Iterate through the set to display the contents
 *   4. Destroying an object when finished
 *   5. Copy the set with the copy constructor and assignment operator
 ******************************************/
void testFill()
{
#ifdef TEST2
   // create 
   cout << "Create an integer Set with the default constructor\n";
   Set <int> s1;

   {
      Set <int> s2;
      cout << "\tEnter numbers, type 0 when done\n";
      int number;
      do
      {
         cout << "\t> ";
         cin  >> number;
         if (number)
            s2.insert(number);
      }
      while (number);

      // copy to s1
      s1 = s2;
      s2.clear();
   }

   // copy to s3;
   Set <int> s3(s1);
   
   // display how big it is
   cout << "\tSize:  " << s3.size() << endl;
   cout << "\tEmpty? " << (s3.empty() ? "Yes" : "No") << endl;

   // iterate through the set
   cout << "Iterate through the set and display the contents\n";
   SetIterator <int> it;
   for (it = s3.begin(); it != s3.end(); ++it)
      cout << "\t" << *it << endl;
#endif // TEST2
}

/******************************************
 * TEST FIND
 * This will test the following:
 *   1. Instantiating a Set object
 *   2. Filling the contents with values
 *   3. Displaying the values using an iterator
 *   4. Prompt for the existance of an item in the set and remove it
 *   5. Display the remaining items in the set
 ******************************************/
void testFind()
{
#ifdef TEST3
   // create a list
   cout << "Create a Set of strings with the default constructor.\n";
   Set <string> s1;

   // fill the Set with text
   cout << "\tEnter text, type \"quit\" when done\n";
   string text;
   do
   {
      cout << "\t> ";
      cin  >> text;
      if (text != "quit")
         s1.insert(text);
   }
   while (text != "quit");

   // display the contents of the Set
   cout << "Use the iterator to display the contents of the Set\n";
   SetIterator <string> it;
   for (it = s1.begin(); it != s1.end(); ++it)
      cout << "\t" << *it << endl;

   // make a copy of the set
   Set <string> s2(s1);
   
   // look for an item in the set
   cout << "Find items in the set and delete.\n";
   cout << "\tEnter words to search for, type \"quit\" when done\n";
   cout << "\t> ";
   cin  >> text;
   do
   {
      SetIterator <string> itEmpty = s1.end();
      SetIterator <string> itFind = s1.find(text);
      if (itFind != itEmpty)
      {
         cout << "\tFound and removed!\n";
         s1.erase(itFind);
      }
      else
         cout << "\tNot found\n";
      cout << "\t> ";
      cin  >> text;
   }
   while (text != "quit");

   // show the list again
   cout << "The remaining set after the items were removed\n";
   for (it = s1.begin(); it != s1.end(); ++it)
      cout << "\t" << *it << endl;

   // show the list before the items were removed
   cout << "The items in the set before the items were removed\n";
   for (it = s2.begin(); it != s2.end(); ++it)
      cout << "\t" << *it << endl;
   
   
#endif // TEST3
}

/**********************************************
 * TEST UNION INTERSECTION
 * This will test the following:
 *    1. Instantiate two Set objects and fill them
 *    2. Display the results of Union
 *    4. Display the results of Intersection
 **********************************************/
void testUnionIntersection()
{
#ifdef TEST4
   cout.setf(ios::fixed | ios::showpoint);
   cout.precision(1);

   // fill the first set with numbers
   Set <float> s1;
   cout << "First set: enter numbers, type 0.0 when done\n";
   float number;
   do
   {
      cout << "\t> ";
      cin  >> number;
      if (number != 0.0)
         s1.insert(number);
   }
   while (number != 0.0);

   // fill the second set with numbers
   Set <float> s2;
   cout << "Second set: enter numbers, type 0.0 when done\n";
   do
   {
      cout << "\t> ";
      cin  >> number;
      if (number != 0.0)
         s2.insert(number);
   }
   while (number != 0.0);
      
   // display intersection
   cout << "s1 && s2:\n";
   Set <float> sIntersection(s1 && s2);
   SetIterator <float> it;
   for (it = sIntersection.begin(); it != sIntersection.end(); ++it)
      cout << "\t" << *it << endl;

   // display union
   cout << "s1 || s2:\n";
   Set <float> sUnion(s1 || s2);
   for (it = sUnion.begin(); it != sUnion.end(); ++it)
      cout << "\t" << *it << endl;

#endif // TEST4
}

/****************************************************************
 * TEST CONST ITERATOR
 * Extra credit: Test the constant iterator
 ****************************************************************/
void testConstIterator()
{
#ifdef TEST5
   // create the set
   Set <int> s1;
   s1.insert(2);
   s1.insert(4);
   s1.insert(6);
   s1.insert(8);

   // display
   cout << "Display the contents using a const iterator\n";
   const Set <int> s2(s1);
   for (SetConstIterator <int> it = s2.cbegin(); it != s2.cend(); ++it)
      cout << '\t' << *it << endl;
   
#endif // TEST5
}

/***********************************************************
 * TEST DIFFERENCE
 * Extra credit: Test the difference operator
 ***********************************************************/
void testDifference()
{
#ifdef TEST6
   // create a set of 10 characters
   Set <char> s1;
   cout << "Please enter 10 characters: ";
   for (int i = 0; i < 10; i++)
   {
      char letter;
      cin >> letter;
      s1.insert(letter);
   }

   // create a second set of 10 characters
   Set <char> s2;
   cout << "Please enter another 10 characters: ";
   for (int i = 0; i < 10; i++)
   {
      char letter;
      cin >> letter;
      s2.insert(letter);
   }

   // s1 - s2
   SetIterator <char> it;
   Set <char> s3(s1 - s2);
   cout << "\t{ ";
   for (it = s1.begin(); it != s1.end(); it++)
      cout << *it << ' ';
   cout << "} - { ";
   for (it = s2.begin(); it != s2.end(); ++it)
      cout << *it << ' ';
   cout << "} = { ";
   for (it = s3.begin(); it != s3.end(); ++it)
      cout << *it << ' ';
   cout << "}\n";

   // s2 - s1
   Set <char> s4(s2 - s1);
   cout << "\t{ ";
   for (it = s2.begin(); it != s2.end(); it++)
      cout << *it << ' ';
   cout << "} - { ";
   for (it = s1.begin(); it != s1.end(); ++it)
      cout << *it << ' ';
   cout << "} = { ";
   for (it = s4.begin(); it != s4.end(); ++it)
      cout << *it << ' ';
   cout << "}\n";
#endif // TEST6
}
