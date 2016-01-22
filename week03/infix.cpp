/***********************************************************************
 * Module:
 *    Week 03, Stack
 *    Brother Helfrich, CS 235
 * Author:
 *    Justin Waite & Winson So
 * Summary:
 *    This program will implement the testInfixToPostfix()
 *    and testInfixToAssembly() functions
 ************************************************************************/

#include <iostream>    // for ISTREAM and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stack.h"     // for STACK
#include <vector>
#include <sstream>
#include "tokenizer.h"
#include "infix.h"
using namespace std;

/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation "5 + 2" into postifx "5 2 +"
 *****************************************************/
string convertInfixToPostfix(const string & infix)
{
   string postfix = "";
   try {
      Tokenizer tokenizer = Tokenizer(infix);
      vector<string> tokens = tokenizer.getVector();
      vector<string>::iterator vit;
      Stack<string> operatorStack;

      for (vit = tokens.begin(); vit != tokens.end(); ++vit)
      {
         // 1. Print operands as they come
         if (!isOperator(*vit))
         {
            postfix += " " + *vit;
         }

         // 2. If the operator stack is empty, the top is ( or the current is (
         // push to the operator stack.
         else if (operatorStack.empty() || operatorStack.top() == "("
            || *vit == "(")
         {
            operatorStack.push(*vit);
         }

         // 3. If a closing ) is found, print operators till ( is found.
         else if (*vit == ")")
         {
            while (operatorStack.top() != "(")
            {
               postfix += " " + operatorStack.top();
               operatorStack.pop();
            }
            operatorStack.pop();
         }

         // 4. If the incomming operator has precendence over top, push it on.
         else if (isOperator(operatorStack.top()) &&
            compareOperators(*vit, operatorStack.top()) == 1)
         {
            operatorStack.push(*vit);
         }

         // 4. If the incomming operator has equal precendence as top, pop and
         // print top, then push the new one on.
         else if (isOperator(operatorStack.top()) &&
            compareOperators(*vit, operatorStack.top()) == 0)
         {
            postfix += " " + operatorStack.top();
            operatorStack.pop();
            operatorStack.push(*vit);
         }

         // 5. If the incomming operator has less precendence than top, pop and
         // print top until an operator with less precendence is found. Push the
         // new one on.
         else if (isOperator(operatorStack.top()) &&
            compareOperators(*vit, operatorStack.top()) == -1)
         {
            bool pushed = false;
            while (!pushed)
            {
               postfix += " " + operatorStack.top();
               operatorStack.pop();

               if (operatorStack.empty() || !isOperator(operatorStack.top()) ||
                  compareOperators(*vit, operatorStack.top()) == 1) //might be a problem
               {
                  operatorStack.push(*vit);
                  pushed = true;
               }
            }
         }
      }

      // 6. Print any remaining operators.
      while (!operatorStack.empty())
      {
         postfix += " " + operatorStack.top();
         operatorStack.pop();
      }
   }
   catch (char const* message)
   {
      cout << message << endl;
   }

   return postfix;
}

/*****************************************************
 * IS OPERATOR
 * Evaluates a given string to determine if it is an
 * operator.
 *****************************************************/
bool isOperator(string s)
{
   return (s == "+" || s == "-" || s == "*" || s == "/" || s == "(" || s == ")"
      || s == "^");
}

/*****************************************************
 * COMPARE OPERATORS
 * Compares two operators to determine which one is
 * of greatest precedence. Returns 1 if lhs is greater
 * 0 if equal and -1 if rhs is greater.
 *****************************************************/
int compareOperators(string lhs, string rhs)
{
   if (lhs == rhs)
      return 0;

   if ((lhs == "+" && rhs == "-") || (rhs == "+" && lhs == "-") ||
      (lhs == "*" && rhs == "/") || (rhs == "*" && lhs == "/"))
      return 0;

   if (lhs == "(")
      return 1;

   if (rhs == "(")
      return -1;

   if (lhs == "^")
      return 1;

   if (rhs == "^")
      return -1;

   if ((lhs == "*" || lhs == "/") && (rhs == "+" || rhs == "-"))
      return 1;

   return -1;
}

/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";

   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }

      // prompt for infix
      cout << "infix > ";
      getline(cin, input);

      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << "\tpostfix: " << postfix << endl << endl;
      }
   }
   while (input != "quit");
}

/**********************************************
 * GET INSTRUCTION
 * Converts a char into an instruction string.
 **********************************************/
string getInstruction(char c)
{
   switch (c)
   {
      case '+': return "ADD";
      case '-': return "SUBTRACT";
      case '*': return "MULTIPLY";
      case '/': return "DIVIDE";
      case '^': return "EXPONENT";
   }
   return "IDK!";
}

/**********************************************
 * CONVERT POSTFIX TO ASSEMBLY
 * Convert postfix "5 2 +" to assembly:
 *     LOAD 5
 *     ADD 2
 *     STORE VALUE1
 **********************************************/
string convertPostfixToAssembly(const string & postfix)
{
   string assembly;
   try
   {
      Tokenizer tokenizer = Tokenizer(postfix);
      vector<string> tokens = tokenizer.getVector();

      Stack<string> operands;
      Stack<string> operators;

      string lhs, rhs;
      int valueNum = 0;

      vector<string>::iterator vit;
      for (vit = tokens.begin(); vit < tokens.end(); ++vit)
      {
         if (!isOperator(*vit))
         {
            operands.push(*vit);
         }
         else
         {
            rhs = operands.top();
            operands.pop();

            lhs = operands.top();
            operands.pop();

            cout << "\tLOAD " << lhs << endl;
            string operatorString = *vit;
            cout << "\t" << getInstruction(operatorString[0]) << " " << rhs
                 << endl;
            cout << "\tSTORE VALUE" << ++valueNum << endl;

            ostringstream sstream;
            sstream << "VALUE" << valueNum;
            operands.push(sstream.str());
         }
      }
   }
   catch (char const* message)
   {
      cout << message << endl;
   }

   return assembly;
}

/*****************************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";

   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }

      // prompt for infix
      cout << "infix > ";
      getline(cin, input);

      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << convertPostfixToAssembly(postfix);
      }
   } while (input != "quit");
}
