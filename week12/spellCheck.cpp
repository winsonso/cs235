/***********************************************************************
 * Module:
 *    Week 12, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    Justin Waite & Winson So
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
#include "spellCheck.h"
#include "hash.h"
// for use of abs function.
#include <stdlib.h>

using namespace std;

/**************************************************
 * STRING HASH
 * A simple hash of strings
 **************************************************/
class SHash : public Hash<string>
{
public:
   SHash(int numBuckets)   throw(const char*): Hash<string>(numBuckets) { }

   SHash(const SHash &rhs) throw(const char*): Hash<string>(rhs) { }

   /*
    * Hash a string.
    * Based off the djb2 string hash function
    * with modifications.
    */
   int hash(const string &str) const
   {
      // An arbitrary number to start with. 12 was chosen because it seemed to
      // bring the number of collisions down by about 10-30 vs other numbers.
      int hash = 12;

      // Loop through each character in the string to perform the hash
      // operations
      for (int i = 0; i < str.length(); i++)
         hash = ((hash << 5) + hash) + (int) str[i];

      // Need to do absolute value because the number could reach max int
      // length and wrap around.
      return abs(hash) % capacity();
   }
};

// load dictionary stub
bool loadDictionary(string &filename, SHash &dict);

// read file stub
bool readFile(string &filename, SHash dictionary, List<string> &misspelled);

// toLowerCase stub
string toLowerCase(string s);

// print list stub
void printList(List<string> list);

/**************************************************
 * SPELL CHECK
 * Prompt the user for a file to spell-check
 **************************************************/

void spellCheck()
{
   string fileName;

   // 3000 was used for the dictionary's bucket size because it leaves only
   // 1412 empty buckets but reduces the collisions to 733 and the largest
   // bucket size is only 5. 5 is trivial to search.
   SHash dict(3000);
   cout << "What file do you want to check? ";
   cin >> fileName;

   string dictionaryFileName = "/home/cs235/week12/dictionary.txt";
   loadDictionary(dictionaryFileName, dict);

   List<string> misspelled;
   readFile(fileName, dict, misspelled);

   printList(misspelled);
}

/**************************************************
 * LOAD DICTIONARY
 * Loads a hash from a dictionary file.
 **************************************************/
bool loadDictionary(string &filename, SHash &dict)
{
   assert(filename != "");

   // Read the file
   ifstream fin(filename.c_str());

   if (fin.fail())
   {
      cout << "Error reading file.\n";
      fin.close();
      return false;
   }

   // Iterate through the words
   string word;
   while (!fin.eof() && fin >> word)
   {
      dict.insert(word);
   }

   fin.close();
   return true;
}

/**************************************************
 * READ FILE
 * Reads a given file and puts any misspelled
 * words into a list.
 **************************************************/
bool readFile(string &filename, SHash dictionary, List<string> &misspelled)
{
   assert(filename != "");

   // Read the file
   ifstream fin(filename.c_str());

   if (fin.fail())
   {
      cout << "Error reading file.\n";
      fin.close();
      return false;
   }

   // Iterate through the words
   string word;
   while (!fin.eof() && fin >> word)
   {
      if (!dictionary.find(toLowerCase(word)))
         misspelled.push_back(word);
   }

   fin.close();
   return true;
}

/**************************************************
 * TO LOWER CASE
 * Returns a lower case version of the given string
 **************************************************/
string toLowerCase(string s)
{
   string temp = s;
   for (int i = 0; i < temp.length(); i++)
      temp[i] = tolower(temp[i]);
   return temp;
}

/**************************************************
 * PRINT LIST
 * Prints the given list or a message saying there
 * is nothing in the list.
 **************************************************/
void printList(List<string> list)
{
   // if there are no misspelled words.
   if (list.empty())
   {
      cout << "File contains no spelling errors\n";
      return;
   }

   // otherwise list the misspelled words.
   cout << "Misspelled: ";

   bool first = true;
   for (ListIterator<string> it = list.begin(); it != list.end(); ++it)
   {
      if (!first)
         cout << ", ";
      else
         first = false;

      cout << *it;
   }
   cout << endl;

}
