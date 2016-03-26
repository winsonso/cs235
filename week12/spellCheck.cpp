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

using namespace std;

/****************************************
 * STRING HASH
 * A simple hash of strings
 ****************************************/
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

      // Loop through each character in the string to get the char int value
      // and the bit shift is performed to randomize
      for (int i = 0; i < str.length(); i++)
         hash = ((hash << 5) + hash) + (int)str[i];

      return abs(hash) % capacity();
   }
};

bool loadDictionary(string &filename, SHash &dict);

/*****************************************
 * SPELL CHECK
 * Prompt the user for a file to spell-check
 ****************************************/

void spellCheck()
{
   string fileName;

   // 5000 was used for the dictionary's bucket size because it leaves only
   // 3000 empty buckets but reduces the collisions to 488 and the largest
   // bucket size is only 4. 4 is trivial to search.
   SHash dict(5000);
   cout << "What file do you want to check? ";
   cin >> fileName;

   string dictionaryFileName = "dictionary.txt";
   loadDictionary(dictionaryFileName, dict);

   cout << "Loaded dictionary:" << endl << "\tSize: " << dict.size()
      << "\n\tCapacity: " << dict.capacity()
      << "\n\tEmpty Buckets: " << dict.getEmptyBuckets()
      << "\n\tCollisions: " << dict.getCollisionCount()
      << "\n\tBiggest Bucket: " << dict.getBiggestBucket()
      << endl;
}

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

/*******************************************
 * READ FILE
 * Reads a given file and puts any misspelled
 * words into a list.
 *******************************************/
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
      if (!dictionary.find(word))
         misspelled.push_back(word);
   }

   fin.close();
   return true;
}
