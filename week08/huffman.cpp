/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    Justin Waite & Winson So
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#include "huffman.h"       // for HUFFMAN() prototype
#include <fstream>
#include <cassert>
using namespace std;

void sortHuffmanCodes(List<Pair<string, string> > & codes);
ListIterator<Huffman> & compare(ListIterator<Huffman> & it1, ListIterator<Huffman> & it2);
bool readFile(List<Huffman> & trees, string path);

/*******************************************
 * HUFFMAN
 * Driver program to exercise the huffman generation code
 *******************************************/
void huffman()
{
   // Prompt user for filename
   string path = "";
   cout << "Enter the filename containing the value frequencies: ";
   cin >> path;
   assert(path != "");

   // Read file
   List<Huffman> trees;
   assert(readFile(trees, path));

   // Keep going until all trees are combined. There can be only one.
   while (trees.size() > 1)
   {
      ListIterator<Huffman> it;
      int currIndex = -1;
      Pair<ListIterator<Huffman>, int> smallest[2];
      for (it = trees.begin(); it != trees.end(); ++it)
      {
         currIndex++;
         // First check if the smallest array isn't carrying anything yet and set to those.
         if (smallest[0].getFirst() == NULL)
         {
            smallest[0] = Pair<ListIterator<Huffman>, int>(it, currIndex);
            continue;
         }
         if (smallest[1].getFirst() == NULL)
         {
            smallest[1] = Pair<ListIterator<Huffman>, int>(it, currIndex);
            continue;
         }

         // Compare the current iterator with those stored in our smallest array.
         // Swap for the smallest one.
         for (int i = 0; i < 2; i++)
         {
            ListIterator<Huffman> temp = smallest[i].getFirst();
            smallest[i].first = compare(temp, it);
            if (smallest[i].getFirst() != temp)
            {
               if (i == 0) {
                  smallest[1].first = compare(temp, smallest[1].first);
                  if (smallest[1].getFirst() == temp)
                     smallest[1].second = smallest[0].getSecond();
               }
               smallest[i].second = currIndex;
               i = 2;
            }
         }
      }

      ListIterator<Huffman> leftMost;
      ListIterator<Huffman> rightMost;

      // Set the left most and right most iterators so we know how to combine
      // them and where to stick the last element in the list.
      leftMost = (smallest[0].getSecond() < smallest[1].getSecond()) ?
                  smallest[0].getFirst() : smallest[1].getFirst();
      rightMost = (smallest[0].getSecond() < smallest[1].getSecond()) ?
                   smallest[1].getFirst() : smallest[0].getFirst();

      (*leftMost).add(*rightMost);
      ListIterator<Huffman> last = trees.rbegin();

      if (rightMost != last)
      {
         trees.insert(rightMost, *last);
         trees.remove(rightMost);
      }
      trees.remove(last);
   }

   List<Pair<string, string> > codes;
   trees.front().extract(codes);

   sortHuffmanCodes(codes);

   ListIterator<Pair<string, string> > lit;
   for (lit = codes.begin(); lit != codes.end(); ++lit)
      cout << (*lit).first << " = " << (*lit).second << endl;
   return;
}

/*******************************************
 * READ FILE
 * Reads a given file and puts the weights and
 * characters into a list of huffman trees.
 *******************************************/
bool readFile(List<Huffman> & trees, string path) {
   assert(path != "");

   // Read the file
   ifstream fin(path.c_str());

   if (fin.fail()) {
      cout << "Error reading file.\n";
      fin.close();
      return false;
   }

   // Iterate through the moves in the file.
   Pair<float, string> data;
   while (!fin.eof() && fin >> data.second >> data.first) {
      if (fin.fail()) break;
      Huffman hm(data);
      trees.push_back(hm);
   }

   fin.close();
   return true;
}

/*******************************************
 * SORT HUFFMAN CODES
 * Sorts a list of codes alphabetically.
 *******************************************/
void sortHuffmanCodes(List<Pair<string, string> > & codes)
{
   if (codes.size() <= 1)
      return;

   List<Pair<string, string> > sorted;
   for (ListIterator<Pair<string, string> > it = codes.begin(); it != codes.end(); ++it)
   {
      if (sorted.size() == 0)
         sorted.push_front(*it);
      else
      {
         bool inserted = false;

         ListIterator<Pair<string, string> > sortedIt;
         for (sortedIt = sorted.begin(); sortedIt != sorted.end(); ++sortedIt)
         {
            if ((*it).first < (*sortedIt).first)
            {
               inserted = true;
               sorted.insert(sortedIt, *it);
               break;
            }
         }

         if (!inserted)
            sorted.push_back(*it);
      }
   }

   codes = sorted;
}

/*******************************************
 * COMPARE
 * Compares two huffman codes by their weights
 * and returns the smaller.
 *******************************************/
ListIterator<Huffman> & compare(ListIterator<Huffman> & it1, ListIterator<Huffman> & it2)
{
   if ((*it1).weight() < (*it2).weight())
      return it1;

   if ((*it2).weight() < (*it1).weight())
      return it2;

   return it1;
}

/*******************************************
 * HUFFMAN NON-DEFAULT CONSTRUCTOR
 * Takes a Pair of float and string and creates
 * a Huffman tree.
 *******************************************/
Huffman :: Huffman(Pair<float, std::string> data)
{
   pTree = new BinaryNode<Pair<float, std::string> >(data);
}

/*******************************************
 * HUFFMAN :: WEIGHT
 * Returns the weight of the given huffman tree.
 *******************************************/
float Huffman :: weight()
{
   return pTree->data.getFirst();
}

/*******************************************
 * HUFFMAN :: ADD
 * Adds two huffman trees together. Whichever
 * one has a smaller weight gets put on the
 * left, bigger on right.
 *******************************************/
void Huffman :: add(const Huffman rhs)
{
   if (pTree == NULL) {
      pTree = rhs.pTree;
      return;
   }

   float w1 = pTree->data.getFirst();
   float w2 = rhs.pTree->data.getFirst();

   BinaryNode<Pair<float, string> > * pRoot;
   Pair<float, string> newData = Pair<float, string>(w1 + w2, "");
   pRoot = new BinaryNode<Pair<float, string> >(newData);

   if (w1 > w2) {
      pRoot->addRight(pTree);
      pRoot->addLeft(rhs.pTree);
   }
   else
   {
      pRoot->addLeft(pTree);
      pRoot->addRight(rhs.pTree);
   }

   pTree = pRoot;
}

/*******************************************
 * HUFFMAN :: Extract
 * Extracts the codes out of the huffman tree.
 *******************************************/
void Huffman :: extract(List<Pair<string, string> > & codes)
{
   extract(pTree, codes);
}

/*******************************************
 * HUFFMAN :: Extract
 * Extracts the codes out of the huffman tree.
 *******************************************/
void Huffman :: extract(BinaryNode<Pair<float, string> > * tree, List<Pair<string, string> > & codes, string path)
{
   if (tree != NULL)
   {
      if (tree->data.getSecond() != "")
      {
         codes.push_back(Pair<string, string>(tree->data.getSecond(), path));
         return;
      }
      if (tree->pRight != NULL)
         extract(tree->pRight, codes, path + "1");

      if (tree->pLeft != NULL)
         extract(tree->pLeft, codes, path + "0");
   }
   return;
}

/*******************************************
 * HUFFMAN :: Extraction operator
 * Prints out a huffman tree's bnode tree.
 *******************************************/
// ostream & operator << (ostream & out, const Huffman & rhs)
// {
//    out << rhs.pTree;
//    return out;
// }
