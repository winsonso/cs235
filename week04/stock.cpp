/***********************************************************************
 * Implementation:
 *    STOCK
 * Summary:
 *    This will contain the implementation for stocksBuySell() as well
 *    as any other function or class implementation you need
 * Author
 *    Justin Waite & Winson So
 **********************************************************************/

#include <iostream>    // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stock.h"     // for STOCK_TRANSACTION
#include "queue.h"     // for QUEUE
#include "dollars.h"   // FOR DOLLARS
#include "portfolio.h" // FOR PORTFOLIO
using namespace std;

/************************************************
 * STOCKS BUY SELL
 * The interactive function allowing the user to
 * buy and sell stocks
 ***********************************************/
void stocksBuySell()
{
   // instructions
   cout << "This program will allow you to buy and sell stocks. "
        << "The actions are:\n";
   cout << "  buy 200 $1.57   - Buy 200 shares at $1.57\n";
   cout << "  sell 150 $2.15  - Sell 150 shares at $2.15\n";
   cout << "  display         - Display your current stock portfolio\n";
   cout << "  quit            - Display a final report and quit the program\n";

   Portfolio portfolio;

   // begin loop
   do {
      cout << "> ";

      string cmd;
      cin >> cmd;

      if (cmd == "display")
         portfolio.display();

      if (cmd == "quit")
         return;

      if (cmd != "buy" && cmd != "sell")
         continue;

      int qty;
      Dollars price;
      cin >> qty;
      cin >> price;

      if (cmd == "buy")
      {
         Transaction t(qty, price);
         portfolio.addBuyTransaction(t);
      }

      if (cmd == "sell")
         portfolio.sellStocks(qty, price);
   }
   while(true);
}
