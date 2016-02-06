/***********************************************************************
 * Implementation:
 *    NOW SERVING
 * Summary:
 *    This will contain the implementation for nowServing() as well as any
 *    other function or class implementations you may need
 * Author
 *    Justin Waite & Winson So
 **********************************************************************/

#include "nowServing.h" // for nowServing() prototype
#include "deque.h"      // for DEQUE
#include <iostream>
#include "request.h"    // for Request
using namespace std;

/************************************************
 * NOW SERVING
 * The interactive function allowing the user to
 * handle help requests in the Linux lab
 ***********************************************/
void nowServing()
{
   HelpSystem hs;
   int count = 0;

   // instructions
   cout << "Every prompt is one minute.  The following input is accepted:\n";
   cout << "\t<class> <name> <#minutes>    : a normal help request\n";
   cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
   cout << "\tnone                         : no new request this minute\n";
   cout << "\tfinished                     : end simulation\n";

   // your code here
   do
   {
      cout << "<" << count++ << "> ";
      string first;
      cin >> first;

      // Break the loop if finished
      if (first == "finished")
         break;

      // Just tick another minute
      if (first == "none")
      {
         hs.tick();
         continue;
      }

      // Parse the user input for a new request.
      bool important = false;
      string className;
      string name;
      int minutes;

      if (first == "!!")
      {
         important = true;
         cin >> className;
      }
      else
         className = first;

      cin >> name;
      cin >> minutes;

      Request req(important, className, name, minutes);
      hs.addRequest(req);

      // Finally tick another minute.
      hs.tick();

   } while(true);

   // finished!
   cout << "End of simulation\n";
}
