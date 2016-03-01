/***********************************************************************
* Program:
*    Week 01, Vector
*    Brother Helfrich, CS 235
* Author:
*    Br. Helfrich
* Summary:
*    This is a driver program to exercise the Vector class.  When you
*    submit your program, this should not be changed in any way.  That being
*    said, you may need to modify this once or twice to get it to work.
************************************************************************/

#include <iostream>       // for CIN and COUT
#include <string>         // because testIterate() uses a Vector of string
#include "vector.h"       // your Vector class needs to be in vector.h
using namespace std;

// prototypes for our four test functions
void testSimple();
void testFill();
void testIterate();
void testCopy();
void testExtra();

// To get your program to compile, you might need to comment out a few
// of these. The idea is to help you avoid too many compile errors at once.
// I suggest first commenting out all of these tests, then try to use only
// TEST1.  Then, when TEST1 works, try TEST2 and so on.
#define TEST1   // for testSimple()
#define TEST2   // for testFill()
#define TEST3   // for testIterate()
#define TEST4   // for testCopy()
//#define TEST5   // for testExtra()

/**********************************************************************
 * MAIN
 * This is just a simple menu to launch a collection of tests
 ***********************************************************************/
int main()
{
   // menu
   cout << "Select the test you want to run:\n";
   cout << "\t1. Just create and destroy a Vector.\n";
   cout << "\t2. The above plus fill the Vector.\n";
   cout << "\t3. The above plus iterate through the Vector.\n";
   cout << "\t4. The above plus copy the Vector.\n";
   cout << "\ta. The extra credit test: constant and reverse iterators.\n";

   // select
   char choice;
   cout << "> ";
   cin  >> choice;
   switch (choice)
   {
      case '1':
         testSimple();
         cout << "Test 1 complete\n";
         break;
      case '2':
         testFill();
         cout << "Test 2 complete\n";
         break;
      case '3':
         testIterate();
         cout << "Test 3 complete\n";
         break;
      case '4':
         testCopy();
         cout << "Test 4 complete\n";
         break;
      case 'a':
         testExtra();
         cout << "Extra Credit complete\n";
         break;
      default:
         cout << "Unrecognized command, exiting...\n";
   }

   return 0;
}

/*******************************************
 * TEST SIMPLE
 * Very simple test for a vector: create and destroy
 ******************************************/
void testSimple()
{
#ifdef TEST1
   // Test1: bool Vector with default constructor
   cout << "Create a bool Vector using default constructor\n";
   Vector <bool> v1;
   cout << "\tSize:     " << v1.size()                   << endl;
   cout << "\tCapacity: " << v1.capacity()               << endl;
   cout << "\tEmpty?    " << (v1.empty() ? "Yes" : "No") << endl;

   {
      // Test2: double Vector with non-default constructor
      cout << "Create a double Vector using the non-default constructor\n";
      Vector <double> v2(10 /*capacity*/);
      cout << "\tSize:     " << v2.size()                   << endl;
      cout << "\tCapacity: " << v2.capacity()               << endl;
      cout << "\tEmpty?    " << (v2.empty() ? "Yes" : "No") << endl;
   }
#endif // TEST1
}

/******************************************
 * TEST FILL
 * This will test the following:
 *   1. Instantiating a Vector object
 *   2. Filling the contents with values
 *   3. Destroying an object when finished
 ******************************************/
void testFill()
{
#ifdef TEST2
   // Test1: integer Vector with default constructor
   {
      // create
      cout << "Create an integer vector with the default constructor\n";
      Vector <int> v1(3);

      cout << "\tEnter numbers, type 0 when done\n";
      int number;
      do
      {
         cout << "\t> ";
         cin  >> number;
         if (number)
            v1.push_back(number);
      }
      while (number);
      cout << "\tSize:     " << v1.size()                   << endl;
      cout << "\tCapacity: " << v1.capacity()               << endl;
      cout << "\tEmpty?    " << (v1.empty() ? "Yes" : "No") << endl;
   }
   cout << "\tFirst vector deleted\n";

   // Test2: character Vector with non-default constructor
   {
      cout << "Create a character Vector with non-default constructor\n";
      Vector <char> v2(2);

      cout << "Insert user-provided characters in the Vector\n";
      cout << "\tEnter characters, type 'q' when done\n";
      char letter;
      do
      {
         cout << "\t> ";
         cin  >> letter;
         if (letter != 'q')
            v2.push_back(letter);
      }
      while (letter != 'q');
      cout << "\tSize:  " << v2.size() << endl;

      // clear the contents
      cout << "\tNow we will clear the contents\n";
      v2.clear();
      cout << "\tSize:     " << v2.size()                   << endl;
      cout << "\tCapacity: " << v2.capacity()               << endl;
      cout << "\tEmpty?    " << (v2.empty() ? "Yes" : "No") << endl;
   }
   cout << "\tSecond Vector deleted\n";
#endif // TEST2
}

/******************************************
 * TEST ITERATE
 * This will test the following:
 *   1. Instantiating a Vector object
 *   2. Filling the contents with values
 *   3. Displaying the values using an iterator
 *   4. Destroying an object when finished
 ******************************************/
void testIterate()
{
#ifdef TEST3
   // create a list
   cout << "Create a Vector of strings with the default constructor.\n";
   Vector <string> v;

   // fill the container with text
   cout << "\tEnter text, type \"quit\" when done\n";
   string text;
   do
   {
      cout << "\t> ";
      cin  >> text;
      if (text != "quit")
         v.push_back(text);
   }
   while (text != "quit");

   // display the contents of the Container
   cout << "Use the iterator to display the contents of the vector\n";
   VectorIterator <string> it;
   for (it = v.begin(); it != v.end(); ++it)
      cout << "\t" << *it << endl;

   // find a given item
   int index;
   cout << "Which item would you like to look up?\n";
   cout << "> ";
   cin  >> index;
   try
   {
      cout << "\t" << v[index] << endl;
      assert(v[index] == v(index));     // test the functor
   }
   catch (const char * s)
   {
      cout << "\t" << s << endl;
   }
#endif // TEST3
}

/**********************************************
 * TEST COPY
 * This will test the following:
 *    1. Instantiate a Vector object using non-default constructor
 *    2. Fill the contents with values
 *    3. Copy one Vector with the values of another
 *    4. Display the contents of the copied Vector with an iterator
 **********************************************/
void testCopy()
{
#ifdef TEST4
   // create a list
   cout << "Create a Vector of floats with the default constructor.\n";
   Vector <float> v1;

   // fill the vector with numbers
   {
      Vector <float> vTemp;
      cout << "\tEnter numbers, type 0.0 when done\n";
      float number;
      do
      {
         cout << "\t> ";
         cin  >> number;
         if (number != 0.0)
            vTemp.push_back(number);
      }
      while (number != 0.0);

      // use the assignment operator
      v1 = vTemp;
   } // vTemp is destroyed

   // copy the container
   cout << "Copy the contents of the Vector into a new Vector\n";
   Vector <float> v2(v1);

   // destroy the old values
   for (int i = 0; i < v1.size(); i++)
      v1[i] = 0.0;

   // display the contents of the Vector
   cout << "Use the iterator to display the contents of the Vector\n";
   VectorIterator <float> it;
   cout.setf(ios::fixed | ios::showpoint);
   cout.precision(1);
   for (it = v2.begin(); it != v2.end(); ++it)
      cout << "\t" << *it << endl;
#endif // TEST4
}

/**********************************************************
 * TEST EXTRA
 * This will test the following for extra credit:
 *    1. Instantiate a Vector object using non-default constructor
 *    2. Fill the contents with values
 *    3. Iterate through the Vector backwards
 *    4. Iterate through the Vector with a constant iterator
 *    5. Iterate through the Vector backwards with a constant iterator
 *********************************************************/
void testExtra()
{
#ifdef TEST5
   // create a list
   cout << "Create a Vector of int with the non-default constructor.\n";
   Vector <int> v1(4);
   VectorIterator <int> it;
   VectorConstIterator <int> cit;

   // fill the vector with numbers
   cout << "\tEnter four integers\n";
   for (int i = 0; i < 4; i++)
   {
      int number;
      cout << "\t> ";
      cin  >> number;
      v1.push_back(number);
   }

   // backwards non-constant iterator
   cout << "Move through the vector backards using a non-constant iterator\n";
   it = v1.begin();
   for (int i = 0; i < 3; i++, ++it)
      ;
   for (int i = 0; i < 4; i++, --it)
      cout << "\t" << *it << endl;

   // copy the vector to a constant vector
   const Vector <int> v2 = v1;

   // forwards constant iterator
   cout << "Move through the vector forwards with a constant iterator\n";
   for (cit = v2.cbegin(); cit != v2.cend(); ++cit)
      cout << "\t" << *cit << endl;

   // backwards constant iterator
   cout << "Move through the vector backwards with a constant iterator\n";
   cit = v1.cbegin();
   for (int i = 0; i < 3; i++, ++cit)
      ;
   for (int i = 0; i < 4; i++, --cit)
      cout << "\t" << *cit << endl;
#endif // TEST5
}
