/***********************************************************************
 * Header:
 *    WholeNumber
 * Summary:
 *    This contains the WholeNumber class which allows for big number
 *    addition.
 *
 *    This will contain the class definition of:
 *        WholeNumber: A class that uses a list to store big numbers.
 *
 * Author
 *    Justin Waite & Winson So
 **********************************************************************/
#ifndef WHOLENUMBER_H
#define WHOLENUMBER_H
#include <iostream>
#include <iomanip>
#include "list.h"

/***********************************************
* WHOLE NUMBER CLASS
* A class that uses a list to store big numbers.
************************************************/
class WholeNumber
{
public:
   WholeNumber() {
      numberSets.push_front(0);
   }

   WholeNumber(unsigned int n);
   WholeNumber(const WholeNumber & rhs);

   WholeNumber & operator += (WholeNumber& rhs);
   WholeNumber & operator =  (WholeNumber& rhs);

   friend std::ostream & operator << (std::ostream & o, WholeNumber & rhs);

private:
   List<unsigned int> numberSets;
};

/***********************************************
* WHOLE NUMBER :: NON-DEFAULT CONSTRUCTOR
* Allows user to pass in an unsigned int and
* does a simple algorithm add the number in.
************************************************/
WholeNumber :: WholeNumber(unsigned int n) {
   numberSets.push_front(0);
   ListIterator<unsigned int> it = numberSets.rbegin();
   unsigned int total = *it + n;

   while (total > 0)
   {
      *it = total % 1000;
      total = total / 1000;

      if (total > 0)
      {
         if (--it == numberSets.rend())
         {
            this->numberSets.push_front(0);
            it = numberSets.begin();
         }
         total += *it;
      }
   }
}

/***********************************************
* WHOLE NUMBER :: operator =
* Copies the rhs numberSets to this->numberSets
************************************************/
WholeNumber & WholeNumber :: operator = (WholeNumber& rhs)
{
   this->numberSets = rhs.numberSets;
   return *this;
}

/***********************************************
* WHOLE NUMBER :: operator +=
* Adds rhs to this using an algorithm to add
* together the different number lists.
************************************************/
WholeNumber & WholeNumber :: operator += (WholeNumber& rhs)
{
   ListIterator<unsigned int> rIt, lIt;
   rIt = rhs.numberSets.rbegin();
   lIt = this->numberSets.rbegin();

   // If there's nothing to add, just leave!
   if (rIt == NULL)
      return *this;

   // Make sure we have at least one set of numbers on the lhs list.
   if (lIt == NULL)
   {
      this->numberSets.push_front(0);
      lIt = this->numberSets.begin();
   }

   // std::cout << "start" << std::endl;

   unsigned int total = *lIt + *rIt;
   while (total > 0 || rIt != rhs.numberSets.rend())
   {
      *lIt = total % 1000;
      total = total / 1000;

      // If there are more rhs numbers to add
      if (rIt != rhs.numberSets.rend() && --rIt != rhs.numberSets.rend())
         total += *rIt;

      // If we still have some carry over or more rhs to add
      if (rIt != rhs.numberSets.rend() || total > 0)
      {
         // If the next iterator is null, add another to the front.
         if (--lIt == this->numberSets.rend())
         {
            this->numberSets.push_front(0);
            lIt = this->numberSets.begin();
         }
         total += *lIt;
      }
   }

   return *this;
}

/***********************************************
* WHOLE NUMBER :: operator <<
* Prints out the big number including commas.
************************************************/
std::ostream & operator << (std::ostream & o, WholeNumber & rhs)
{
   ListIterator<unsigned int> it;
   for (it = rhs.numberSets.begin(); it != rhs.numberSets.end(); ++it)
   {
      if (it == rhs.numberSets.begin())
         o << *it;
      else
         o << ',' << std::setfill('0') << std::setw(3) << *it;
   }

   return o;
}

#endif //WHOLENUMBER_H
