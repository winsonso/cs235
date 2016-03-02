/***********************************************************************
* Program:
*    Week 09, Binary Search Trees and the Binary Sort
*    Brother Helfrich, CS 235
* Author:
*    Br. Helfrich
* Summary:
*    This is a driver program to exercise the BST class.  When you
*    submit your program, this should not be changed in any way.  That being
*    said, you may need to modify this once or twice to get it to work.
************************************************************************/

#include <iostream>      // for CIN and COUT
#include <string>        // for STRING
#include "bst.h"         // for BST class which should be in bst.h
#include "sortBinary.h"  // for sortBinary()
using namespace std;


// prototypes for our four test functions
void testSimple();
void testAdd();
void testIterate();
void testDelete();
void testSort();

// To get your program to compile, you might need to comment out a few
// of these. The idea is to help you avoid too many compile errors at once.
// I suggest first commenting out all of these tests, then try to use only
// TEST1.  Then, when TEST1 works, try TEST2 and so on.
#define TEST1   // for testSimple()
#define TEST2   // for testAdd()
#define TEST3   // for testIterate()
#define TEST4   // for testDelete()

/**********************************************************************
 * MAIN
 * This is just a simple menu to launch a collection of tests
 ***********************************************************************/
int main()
{
   // menu
   cout << "Select the test you want to run:\n";
   cout << "\t1. Just create and destroy a BST\n";
   cout << "\t2. The above plus add a few nodes\n";
   cout << "\t3. The above plus display the contents of a BST\n";
   cout << "\t4. The above plus find and delete nodes from a BST\n";
   cout << "\ta. To test the binarySort() function\n";

   // select
   char choice;
   cout << "> ";
   cin  >> choice;
   switch (choice)
   {
      case 'a':
         testSort();
         break;
      case '1':
         testSimple();
         cout << "Test 1 complete\n";
         break;
      case '2':
         testAdd();
         cout << "Test 2 complete\n";
         break;
      case '3':
         testIterate();
         cout << "Test 3 complete\n";
         break;
      case '4':
         testDelete();
         cout << "Test 4 complete\n";
         break;
      default:
         cout << "Unrecognized command, exiting...\n";
   }

   return 0;
}

/*******************************************
 * TEST SIMPLE
 * Very simple test for a BST: create and destroy
 ******************************************/
void testSimple()
{
#ifdef TEST1
   try
   {
      // Test1: a bool BST
      cout << "Create a bool Binary Search Tree "
           << "using the default constructor\n";
      BST <bool> tree;

      // Test2: double BST
      cout << "Create a double Binary Search Tree\n";
      BST <double> * pTree = new BST <double>;
      delete pTree;
   }
   catch (const char * error)
   {
      cout << error << endl;
   }
#endif //TEST1
}

/*******************************************
 * TEST ADD
 * Add a few nodes together to create a tree, then
 * destroy it when done
 *****************************************/
void testAdd()
{
#ifdef TEST2
   try
   {
      // create
      cout << "Create an integer Binary Search Tree\n";
      BST <int> tree1;

      tree1.insert(8);     //               8
      tree1.insert(4);     //          +----+----+
      tree1.insert(12);    //          4         12
      tree1.insert(2);     //       +--+--+   +--+--+
      tree1.insert(6);     //       2     6   9     13
      tree1.insert(9);     //     +-+   +-+   +-+
      tree1.insert(13);    //     0     5       11
      tree1.insert(0);
      tree1.insert(5);
      tree1.insert(11);

      BSTIterator<int> it = tree1.begin();

      // copy the tree to another
      BST <int> tree2(tree1);

      cout << "\tTree deleted\n";
   }
   catch (const char * error)
   {
      cout << error << endl;
   }
#endif // TEST2
}

/*******************************************
 * TEST ITERATE
 * We will build a binary tree and display the
 * results on the screen
 ******************************************/
void testIterate()
{
#ifdef TEST3
   cout.setf(ios::fixed | ios::showpoint);
   cout.precision(1);

   //
   // An empty tree
   //
   try
   {
      cout << "Create an empty bool BST\n";
      BST <bool> tree;
      BSTIterator <bool> it;
      cout << "\tEmpty tree\n";

      // display the contents
      cout << "\tContents: ";
      for (it = tree.begin(); it != tree.end(); ++it)
         cout << *it << " ";
      cout << endl;

      // tree deleted
      cout << "\tTree deleted\n";
   }
   catch (const char * s)
   {
      cout << "Thrown exception: " << s << endl;
   }

   //
   // A tree with three nodes
   //
   try
   {
      cout << "Create an double BST\n";
      BST <double> tree1;
      BST <double> tree2;
      BSTIterator <double> it;

      // fill the tree
      cout << "\tFill the BST with: 2.2  1.1  3.3  \n";
      tree1.insert(2.2);     //          2.2
      tree1.insert(1.1);     //     +-----+-----+
      tree1.insert(3.3);     //    1.1         3.3
      tree2 = tree1;

      // display the contents forward
      cout << "\tContents forward:  ";
      for (it = tree1.begin(); it != tree1.end(); ++it)
         cout << *it << "  ";
      cout << endl;
      tree1.clear();

      // display the contents backwards
      cout << "\tContents backward: ";
      for (it = tree2.rbegin(); it != tree2.rend(); --it)
         cout << *it << "  ";
      cout << endl;

      // tree deleted
      cout << "\tTree deleted\n";
      }
   catch (const char * s)
   {
      cout << "Thrown exception: " << s << endl;
   }

   //
   // a non-trivial tree
   //
   try
   {
      cout << "Create a string BST\n";
      BST <string> tree1;
      BST <string> tree2;
      BSTIterator <string> it;

      // fill the tree
      cout << "\tFill the BST with: f  c  i  b  e  g  j  a  d  h  \n";
      tree1.insert(string("f"));     //               f
      tree1.insert(string("c"));     //          +----+----+
      tree1.insert(string("i"));     //          c         i
      tree1.insert(string("b"));     //       +--+--+   +--+--+
      tree1.insert(string("e"));     //       b     e   g     j
      tree1.insert(string("g"));     //     +-+   +-+   +-+
      tree1.insert(string("j"));     //     a     d       h
      tree1.insert(string("a"));
      tree1.insert(string("d"));
      tree1.insert(string("h"));
      tree2 = tree1;

      // display the contents forward
      cout << "\tContents forward:  ";
      for (it = tree1.begin(); it != tree1.end(); ++it)
         cout << *it << "  ";
      cout << endl;
      tree1.clear();

      // display the contents backwards
      cout << "\tContents backward: ";
      for (it = tree2.rbegin(); it != tree2.rend(); --it)
         cout << *it << "  ";
      cout << endl;

      // tree deleted
      cout << "\tTree deleted\n";
   }
   catch (const char * s)
   {
      cout << "Thrown exception: " << s << endl;
   }
#endif // TEST3
}

/*******************************************
 * TEST DELETE
 * Insert a few items into a tree, then delete a few items
 *******************************************/
void testDelete()
{
#ifdef TEST4
   try
   {
      cout << "Create a char BST\n";
      BST <char> tree;

      // Fill the tree
      cout << "\tFill the tree with: G F A E C B D J H I O M K L N P\n";
      tree.insert('G');
      tree.insert('F'); //                       G
      tree.insert('A'); //          +------------+------------+
      tree.insert('E'); //          F                         J
      tree.insert('C'); //   +------+                  +------+------+
      tree.insert('B'); //   A                         H             O
      tree.insert('D'); //   +---+                     +---+     +---+---+
      tree.insert('J'); //       E                         I     M       P
      tree.insert('H'); //    +--+                            +--+--+
      tree.insert('I'); //    C                               K     N
      tree.insert('O'); //  +-+-+                             +-+
      tree.insert('M'); //  B   D                               L
      tree.insert('K');
      tree.insert('L');
      tree.insert('N');
      tree.insert('P');

      // display the tree
      cout << "\tContents without removal: ";
      BSTIterator <char> it;
      for (it = tree.begin(); it != tree.end(); ++it)
         cout << *it << ' ';
      cout << endl;

      //
      // Remove node D: leaf
      //

      cout << "Remove a leaf node\n";

      // find node 'D' and remove it
      it = tree.find('D');
      if (it == tree.end())
         cout << "\tNode not found!\n";
      else
         cout << "\tNode '" << *it << "' found\n";
      if (it != tree.end())
         tree.remove(it);

      // display the tree again
      cout << "\tContents after 'D' was removed: ";
      for (it = tree.begin(); it != tree.end(); ++it)
         cout << *it << ' ';
      cout << endl;

      // look for node 'D' again
      it = tree.find('D');
      if (it == tree.end())
         cout << "\tNode not found!\n";
      else
         cout << "\tNode '" << *it << "' found\n";

      //
      // Remove node E: one child (left)
      //

      cout << "Remove a one-child node\n";

      // look for node 'E' and remove it
      it = tree.find('E');
      if (it == tree.end())
         cout << "\tNode not found!\n";
      else
         cout << "\tNode '" << *it << "' found\n";
      if (it != tree.end())
         tree.remove(it);

      // display the tree again
      cout << "\tContents after 'E' was removed: ";
      for (it = tree.begin(); it != tree.end(); ++it)
         cout << *it << ' ';
      cout << endl;

      //
      // Remove node J: two children where 'K' is inorder successor
      //

      cout << "Remove a two-child node\n";

      // look for node 'J' and remove it
      it = tree.find('J');
      if (it == tree.end())
         cout << "\tNode not found!\n";
      else
         cout << "\tNode '" << *it << "' found\n";
      if (it != tree.end())
         tree.remove(it);

      // display the tree again
      cout << "\tContents after 'J' was removed: ";
      for (it = tree.begin(); it != tree.end(); ++it)
         cout << *it << ' ';
      cout << endl;

      //
      // Remove node G: the root
      //

      cout << "Remove the root\n";

      // look for node 'G' and remove it
      it = tree.find('G');
      if (it == tree.end())
         cout << "\tNode not found!\n";
      else
         cout << "\tNode '" << *it << "' found\n";
      if (it != tree.end())
         tree.remove(it);

      // display the tree again
      cout << "\tContents after 'G' was removed: ";
      for (it = tree.begin(); it != tree.end(); ++it)
         cout << *it << ' ';
      cout << endl;


      cout << "\tTree deleted\n";
   }
   catch (const char * s)
   {
      cout << "Thrown exception: " << s << endl;
   }
#endif // TEST4
}

/***************************************
 * TEST SORT
 * Sort three things using the binary sort
 ***************************************/
void testSort()
{
   cout.setf(ios::fixed | ios::showpoint);
   cout.precision(1);

   //
   // Test a small set of strings
   //

   cout << "Four string objects\n";

   // before
   string array1[4] =
   {
      string("Beta"), string("Alpha"), string("Epsilon"), string("Delta")
   };
   int size1 = sizeof(array1) / sizeof(array1[0]);
   cout << "\tBefore: " << array1[0];
   for (int i = 1; i < size1; i++)
      cout << ", " << array1[i];
   cout << endl;

   // sort
   sortBinary(array1, size1);

   // after
   cout << "\tAfter:  " << array1[0];
   for (int i = 1; i < size1; i++)
      cout << ", " << array1[i];
   cout << endl;

   //
   // Test a medium set of floats
   //

   cout << "Twenty one-decimal numbers\n";

   // before
   float array2[20] =
   {
      5.1, 2.4, 8.2, 2.7, 4.7, 1.8, 9.9, 3.4, 5.0, 1.0,
      4.4, 3.4, 8.3, 2.9, 1.7, 7.9, 9.5, 9.3, 3.6, 2.9
   };
   int size2 = sizeof(array2) / sizeof(array2[0]);
   cout << "\tBefore:\t" << array2[0];
   for (int i = 1; i < size2; i++)
      cout << (i % 10 == 0 ? ",\n\t\t" : ", ")
           << array2[i];
   cout << endl;

   // sort
   sortBinary(array2, size2);

   // after
   cout << "\tAfter:\t" << array2[0];
   for (int i = 1; i < size2; i++)
      cout << (i % 10 == 0 ? ",\n\t\t" : ", ")
           << array2[i];
   cout << endl;

   //
   // Test a large set of integers
   //

   cout << "One hundred three-digit numbers\n";

   // before
   int array3[100] =
   {
      889, 192, 528, 675, 154, 746, 562, 482, 448, 842, 929, 330, 615, 225,
      785, 577, 606, 426, 311, 867, 773, 775, 190, 414, 155, 771, 499, 337,
      298, 242, 656, 188, 334, 184, 815, 388, 831, 429, 823, 331, 323, 752,
      613, 838, 877, 398, 415, 535, 776, 679, 455, 602, 454, 545, 916, 561,
      369, 467, 851, 567, 609, 507, 707, 844, 643, 522, 284, 526, 903, 107,
      809, 227, 759, 474, 965, 689, 825, 433, 224, 601, 112, 631, 255, 518,
      177, 224, 131, 446, 591, 882, 913, 201, 441, 673, 997, 137, 195, 281,
      563, 151,
   };
   int size3 = sizeof(array3) / sizeof(array3[0]);
   cout << "\tBefore:\t" << array3[0];
   for (int i = 1; i < size3; i++)
      cout << (i % 10 == 0 ? ",\n\t\t" : ", ")
           << array3[i];
   cout << endl;

   // sort
   sortBinary(array3, size3);

   // after
   cout << "\tAfter:\t" << array3[0];
   for (int i = 1; i < size3; i++)
      cout << (i % 10 == 0 ? ",\n\t\t" : ", ")
           << array3[i];
   cout << endl;
}
