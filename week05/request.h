/***********************************************************************
* Header:
*    Request, HelpSystem
* Summary:
*    This file contains the Request class and HelpSystem class. The
*    Request class holds information regarding a student's help request
*    for the linux lab incuding class, name, and minutes required.
*    The HelpSystem class manages the current and incomming requests.
*    This will contain the class definition of:
*        Request         : A class that holds info about a help request.
*        HelpSystem      : A class that controlls the flow of requests.
* Author
*    Justin Waite & Winson So
************************************************************************/
#ifndef REQUEST_H
#define REQUEST_H

#ifndef NULL
#define NULL 0
#endif

#include <cassert>
#include <iostream>
#include <string>
#include "deque.h"

/************************************************
 * REQUEST CLASS
 * A container that holds information reagrding
 * a linux lab help request.
 ***********************************************/
class Request
{
public:
   // default constructor
   Request() : important(false), className(""), studentName(""), minutes(0) {}

   // non-default constructor
   Request(bool important, std::string className, std::string studentName, int minutes);

   // Accessors
   bool getImportant() const    { return important;    }
   std::string getClass() const { return className;    }
   std::string getName() const  { return studentName;  }
   int getMinutes() const       { return minutes;      }

   // Decrease minutes by 1.
   void decreaseMinutes()       { minutes -= 1;        }

private:
   // Used to identify if it is an emergency
   bool important;

   // Class name
   std::string className;

   // student name
   std::string studentName;

   // number of minutes to help student.
   int minutes;
};

/************************************************
 * REQUEST :: NON-DEFAULT CONSTRUCTOR
 ***********************************************/
Request :: Request(bool important, std::string className, std::string studentName, int minutes)
{
   this->important = important;
   this->className = className;
   this->studentName = studentName;
   this->minutes = minutes;
}

/************************************************
 * HELP SYSTEM CLASS
 * The HelpSystem class holds a deque of requests
 * and manages these requests for students that
 * need help.
 ***********************************************/
class HelpSystem
{
public:
   HelpSystem() : pCurrent(NULL) {}

   // << operator
   friend std::ostream & operator << (std::ostream & out, HelpSystem & rhs);

   // Adds a request to the current request or the deque.
   void addRequest(Request req);

   // Simulates a minute's passing.
   void tick();

private:
   // Deque to hold the requests.
   Deque<Request> requests;

   // The current request
   Request current;

   // Points to the current request, used to check if a current exists.
   Request* pCurrent;
};

/************************************************
 * HELP SYSTEM :: EXTRACTION OPERATOR
 ***********************************************/
std::ostream & operator << (std::ostream & out, HelpSystem & rhs)
{
   // If there is nothing to display, then leave.
   if (rhs.pCurrent == NULL)
      return out;

   out << ((rhs.current.getImportant()) ? "\tEmergency for " : "\tCurrently serving ")
       << rhs.current.getName()
       << " for class " << rhs.current.getClass()
       << ". Time left: " << rhs.current.getMinutes();
   return out;
}

/************************************************
 * HELP SYSTEM :: ADD REQUEST
 * Adds a new request. If there is not a current
 * request, adds it to the current variable. If
 * it is an Emergency, adds to the front of the
 * deque, otherwise to the back.
 ***********************************************/
void HelpSystem :: addRequest(Request req)
{
   // No need to help this request...
   if (req.getMinutes() <= 0)
      return;

   // Set a new current request if none exist.
   if (pCurrent == NULL)
   {
      current = req;
      pCurrent = &req;
      return;
   }

   // Otherwise add to the deque.
   if (req.getImportant())
      requests.push_front(req);
   else
      requests.push_back(req);
}

/************************************************
 * HELP SYSTEM :: TICK
 * Simulates a passing of one minute. If the
 * current request is out of time then the next
 * in line becomes the current request.
 ***********************************************/
void HelpSystem :: tick()
{
   // If we dont have any requests, just leave.
   if (pCurrent == NULL && requests.empty())
      return;

   // Display the current request being helped.
   std::cout << *this << std::endl;

   // Decrease the remaining minutes for the current request.
   current.decreaseMinutes();

   // If the current request has reached 0
   if (current.getMinutes() <= 0)
   {
      // If there are no more requests in the queue set pCurrent to NULL;
      if (requests.empty())
      {
         pCurrent = NULL;
         return;
      }

      // Copy the front request to current and pop the front.
      current = requests.front();
      pCurrent = &current;
      requests.pop_front();
   }
}

#endif // REQUEST_H
