/***********************************************************************
 * Module:
 *    Week 10, WORD COUNT
 *    Brother Helfrich, CS 235
 * Author:
 *    Winson So & Justin Waite
 * Summary:
 *    This program will implement the wordCount() function
 ************************************************************************/

#include <fstream>
#include "map.h"       // for MAP
#include "wordCount.h" // for wordCount() prototype
using namespace std;
//void readFile(Map <string, Count> & counts, const string & fileName);

/*****************************************************
 * WORD COUNT
 * Prompt the user for a file to read, then prompt the
 * user for words to get the count from
 *****************************************************/
void wordCount()
{
  Map<int, string> count;
  string fileName;
  cout<< "What is the filename to be counted? ";
  cin>> fileName;

 // Read the file
  ifstream fin;
  fin.open(fileName.c_str());

  string str;
  int i = 0;
  while(fin >> str)
  {
     count[i] = str;
     i++;
  }
 // Close the file
  fin.close();

   cout << "What word whose frequency is to be found. Type ! when done";
   string input;
   MapIterator<int, string> it;
   cout<< endl << "> ";
   cin >> input;
  while(input != "!")
  {
     cout << "\t" << input << " : ";
     int frequency = 0;
     for(it = count.begin(); it!=count.end(); it++)
     {
        if(*it == input)
           frequency++;
     }
     cout << frequency << endl << "> ";
     cin >> input;
 }
}
