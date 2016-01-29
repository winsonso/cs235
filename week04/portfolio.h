/***********************************************************************
 * Header:
 *    SELL HISTORY ENTRY & TRANSACTION & PORTFOLIO
 * Summary:
 *    The Portfolio class holds history of ones stock trading. The
 *    Portfolio contains a queue of transactions (purchased stocks)
 *    that can be added to or sold, and a history of the sales along
 *    with profits made.
 * Author
 *    Justin Waite & Winson So
 ************************************************************************/

#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <iostream>  // for OSTREAM and ISTREAM
#include "dollars.h" // for DOLLARS
#include "queue.h"   // for QUEUE
#include <vector>    // for VECTOR

/************************************************
 * SELL HISTORY ENTRY
 * An entry for stock selling history, containing
 * quantity, price, and profit.
 ***********************************************/
struct SellHistoryEntry
{
   int quantity;
   Dollars price;
   Dollars profit;
};

/************************************************
 * Transaction
 * Holds data for a stock purchase, including
 * quantity and price. Quantity is lowered as the
 * stocks get sold.
 ***********************************************/
class Transaction
{
public:
   // Default constructor
   Transaction() : quantity(0), price(0) {}

   //Non-Default constructor
   Transaction(int quantity, Dollars price) : quantity(quantity), price(price){}

   //Remove specified amount of stocks
   void removeStocks(int qty) throw (const char*);

   // Return the number of stocks left
   int size () const { return quantity; }

   // Return the price paid for the stocks.
   Dollars getPrice () const { return price; }

private:
   // How many stocks are left from this transaction
   int quantity;

   // How much was paid for these stocks
   Dollars price;
};

/**********************************************
 * TRANSACTION : REMOVE STOCKS
 * Remove the specified amount of stocks.
 **********************************************/
void Transaction :: removeStocks(int qty) throw (const char*)
{
   if (qty > quantity)
      throw "ERROR: attempting to remove more stocks than available.";

   quantity -= qty;
}

/************************************************
 * PORTFOLIO
 * The portfolio class holds a queue of
 * purchase transactions, and a history of sales
 ***********************************************/
class Portfolio
{
public:
   // Default Constructor
   Portfolio() {}

   // Adds a purchase transaction to the queue.
   void addBuyTransaction(Transaction transaction);

   // Removes stocks from purchase transactions and makes a sales record.
   void sellStocks(int qty, Dollars price);

   // Prints out the current state of the portfolio.
   void display();

private:
   // Queue to hold the purchase transactions
   Queue<Transaction> buyTransactions;

   // Vector to hold sale history
   std::vector<SellHistoryEntry> sellTransactions;
};

/**********************************************
 * PORTFOLIO : ADD BUY TRANSACTION
 * Adds a purchase transaction to the queue.
 **********************************************/
void Portfolio :: addBuyTransaction(Transaction transaction)
{
   buyTransactions.push(transaction);
}

/**********************************************
 * PORTFOLIO : SELL STOCKS
 * Removes stocks from purchase transactions
 * and makes a sales record.
 **********************************************/
void Portfolio :: sellStocks(int qty, Dollars price)
{
   int remaining = qty;

   while (remaining > 0)
   {
      if (buyTransactions.empty())
      {
         std::cout << "You has ran out of stocks :(" << std::endl;
         return;
      }

      Transaction& front = buyTransactions.front();
      int count = (remaining > front.size()) ? front.size() : remaining;
      Dollars val = (price - front.getPrice()) * count;

      SellHistoryEntry entry;
      entry.quantity = count;
      entry.price = price;
      entry.profit = val;
      sellTransactions.push_back(entry);

      remaining -= count;
      front.removeStocks(count);
      if (front.size() == 0)
         buyTransactions.pop();
   }
}

/**********************************************
 * PORTFOLIO : DISPLAY
 * Prints out the current state of the
 * portfolio.
 **********************************************/
void Portfolio :: display()
{
   // Purcases/currently owned
   if (!buyTransactions.empty())
   {
      std::cout << "Currently held:" << std::endl;
      Queue<Transaction> temp = buyTransactions;
      while (!buyTransactions.empty())
      {
         std::cout << "\tBought " << buyTransactions.front().size()
                   << " shares at " << buyTransactions.front().getPrice()
                   << std::endl;
         buyTransactions.pop();
      }
      buyTransactions = temp;
   }

   // Sales history
   if (!sellTransactions.empty())
   {
      std::cout << "Sell History:" << std::endl;
      for (int i = 0; i < sellTransactions.size(); i++)
      {
         std::cout << "\tSold " << sellTransactions[i].quantity
                   << " shares at " << sellTransactions[i].price
                   << " for a profit of " << sellTransactions[i].profit
                   << std::endl;
      }
   }

   // Overall profit made.
   Dollars proceeds;
   for (int i = 0; i < sellTransactions.size(); i++)
      proceeds += sellTransactions[i].profit;
   std::cout << "Proceeds: " << proceeds << std::endl;
}

#endif // PORTFOLIO_H
