/***********************************************************************
 * Header:
 *    Go Fish
 * Summary:
 *    This will contain just the prototype for the goFish() function
 * Author
 *    Justin Waite & Winson So
 ************************************************************************/

#ifndef GO_FISH_H
#define GO_FISH_H

#include "set.h"
#include "card.h"

/**************************************************
 * GO FISH
 * Play the game of "Go Fish"
 *************************************************/
void goFish();
bool readFile(Set<Card> & cards);


#endif // GO_FISH_H
