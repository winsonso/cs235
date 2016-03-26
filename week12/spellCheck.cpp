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
// Input the dictionary into hash table
ifstream fin("dictionary.txt");

string dict;
while(fin >> dict)
{
  hash.insert(dict);
}
fin.close();
cout << "\tSize:     " << hash.size()                   << endl;
cout << "\tCapacity: " << hash.capacity()               << endl;
cout << "\tEmpty?    " << (hash.empty() ? "Yes" : "No") << endl;

// Read the file and check if it is misspelled
cout << "What file do you want to check? ";
 cin >> fileName;
    ifstream check(fileName.c_str());
    if (check.fail())
    {
       cout << "Error reading file.\n";
       check.close();
    }

    string missSpell;
    string word;
    while(check >> word)
    {
      string tmp = word;
      tmp[0] = tolower(tmp[0]);
      if(!hash.find(tmp))
      {
         if (missSpell.size() != 0)
            missSpell += ", ";
            missSpell += word;
      }
    }
   if (missSpell !="")
      cout << "Misspelled: " << missSpell << endl;
   else
      cout << "File contains no spelling errors\n";
}
