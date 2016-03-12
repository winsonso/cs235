/***********************************************************************
 * Module:
 *    Week 10, WORD COUNT
 *    Brother Helfrich, CS 235
 * Author:
 *    Winson So & Justin Waite
 * Summary:
 *    This program will implement the wordCount() function
 ************************************************************************/

#include <iostream>
#include <fstream>
#include "map.h"       // for MAP
#include "wordCount.h" // for wordCount() prototype

using namespace std;

// reads the file.
bool readFile(string &filename, Map<string, int> &map);

/*****************************************************
 * WORD COUNT
 * Prompt the user for a file to read, then prompt the
 * user for words to get the count from
 *****************************************************/
void wordCount()
{
   Map<string, int> wordMap;
   string fileName;
   cout << "What is the filename to be counted? ";
   cin >> fileName;

   assert(readFile(fileName, wordMap));

   string input;
   cout << "What word whose frequency is to be found. Type ! when done\n";

   // Read the file
   while (input != "!")
   {
      cout << "> ";
      cin >> input;

      if (input != "!")
      {
         cout << "\t" << input << " : ";
         cout << wordMap[input] << endl;
      }
   }
}

/*******************************************
 * READ FILE
 * Reads a given file and puts the words and
 * their frequencies into the given map.
 *******************************************/
bool readFile(string &filename, Map<string, int> &map)
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

   // Iterate through the moves in the file.
   string word;
   while (!fin.eof() && fin >> word)
   {
      if (fin.fail())
      {
         cout << "Error during file read.\n";
         fin.close();
         return false;
      }

      map[word]++;
   }

   fin.close();
   return true;
}
