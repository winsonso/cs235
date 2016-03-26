/***********************************************************************
 * Module:
 *    Week 12, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name here>
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "spellCheck.h"
#include "hash.h"
using namespace std;
/****************************************
 * S HASH
 * A simple hash of strings
 ****************************************/
class SHash: public Hash<string>
{
public:
   SHash(int numBuckets)   throw (const char*): Hash<string> (numBuckets) {}
   SHash(const SHash &rhs) throw (const char*): Hash<string> (rhs)        {}

   int hash (const string &str) const
   {
   int sum = 0;
   for (unsigned int i = 0; i < str.size(); i++)
      sum += str[i];
   return sum % capacity();
   }
};

/*****************************************
 * SPELL CHECK
 * Prompt the user for a file to spell-check
 ****************************************/

void spellCheck()
{
  string fileName;
  SHash hash(101);
  cout << "What file do you want to check? ";
  cin >> fileName;
  // Read the file
  // Read the file
  ifstream fin(filename.c_str());

  if (fin.fail())
  {
     cout << "Error reading file.\n";
     fin.close();
     return false;
  }

  string word;
     while(fin >> word)
     {
        hash.insert(word);
     }
     fin.close();

}
