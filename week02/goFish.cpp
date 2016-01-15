/***********************************************************************
 * Program:
 *    Assignment 01, Go Fish
 *    Brother Helfrich, CS 235
 * Author:
 *    Justin Waite & Winson So
 * Summary:
 *    This is all the functions necessary to play Go Fish!
 *
 *    Estimated:  2.0 hrs
 *    Actual:     3.5 hrs
 *      The most difficult part was getting our pair programming dialed
 *      in so we were working efficiently. Also remembering how to read
 *      from files took a minute to figure out.
 ************************************************************************/

#include <iostream>
#include <fstream>
#include "set.h"

// #include <Set>
#include "card.h"
#include "goFish.h"
using namespace std;

#define LINUX_LAB

/**********************************************************************
 * GO FISH
 * The function which starts it all
 ***********************************************************************/
void goFish()
{
   Set<Card> cards;            // Declare the cards Set.
   unsigned short matches = 0; // Save the bits! Use a short :)

   assert(readFile(cards));    // Make sure we read the file in.

   cout << "We will play 5 rounds of Go Fish.  Guess the card in the hand"
        << endl;

   // Begin the 5 rounds using a simple for-loop.
   for (int i = 1; i <= 5; i++)
   {
      Card card;                                   // Declare a temporary Card
      cout << "round " << i << ": ";               // State the current round
      cin >> card;                                 // Have user input a card
                                                   // type

      SetIterator<Card> search = cards.find(card); // Search for card in cards

      if (search != cards.end())                   // If the card was found
      {
         cout << "\tYou got a match!" << endl;     // Let the user know
         cards.erase(search);                      // Remove the card from the
                                                   // Set.
         matches++;                                // Increase the score.
      }
      else
      {
         cout << "\tGo Fish!" << endl; // Oh well, try again...
      }
   }
   cout << "You have " << matches << " matches!" << endl;
   cout << "The remaining cards: ";

   // Iterate through remaining cards.
   for (SetIterator<Card>it = cards.begin(); it != cards.end(); ++it)
   {
      cout << (it == cards.begin() ? "" : ", ") << *it; // Display the card name
   }
   cout << endl;          // Close up shop!
}

bool readFile(Set<Card>& cards) {
   string filename;

#ifdef LINUX_LAB
   filename = "/home/cs235/week02/hand.txt";
#endif // LINUX_LAB

#ifndef LINUX_LAB
   filename = "hand.txt";
#endif // LINUX_LAB

   assert(filename != "");

   // Read the file
   ifstream fin(filename.c_str());

   if (fin.fail()) {
      cout << "Error reading file.\n";
      fin.close();
      return false;
   }

   // Iterate through the moves in the file.
   while (!fin.eof()) {
      Card newCard;
      fin >> newCard;

      if (fin.fail()) break;

      // Insert the new card;
      cards.insert(newCard);
   }

   fin.close();
   return true;
}
