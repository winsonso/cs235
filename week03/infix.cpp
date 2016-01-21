/***********************************************************************
 * Module:
 *    Week 03, Stack
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name here>
 * Summary:
 *    This program will implement the testInfixToPostfix()
 *    and testInfixToAssembly() functions
 ************************************************************************/

#include <iostream>    // for ISTREAM and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stack.h"     // for STACK
using namespace std;
int priority(char a)
{
   int temp;
   if (a == '^')
      temp = 3;
   else if (a == '*' || a == '/')
      temp = 2;
   else if (a == '+' || a == '-')
      temp = 1;
   else
      temp = -1;
   return temp;

}

// Function to perform an operation and return output.
bool hasHigherPrecedence(char op1, char op2)
{
	int op1Weight = priority(op1);
	int op2Weight = priority(op2);

	if (op1Weight > op2Weight)
	{
	   return true;
	} else{
	   return false;
	}

}

//operand
bool isOperand(char a)
{
   if(a >= '0' && a <= '9')
      return true;
   else if(a >= 'a' && a <= 'z')
      return true;
   else if(a >= 'A' && a <= 'Z')
      return true;
   else if(a == '.')
      return true;
   else if(a == ' ')
      return true;
   else
      return false;
}

// Function to verify whether a character is operator symbol or not.
bool isOperator(char C)
{
	if(C == '+' || C == '-' || C == '*' || C == '/' || C == '^' || C == '(' || C ==')')
		return true;

	return false;
}

/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation "5 + 2" into postifx "5 2 +"
 *****************************************************/
string convertInfixToPostfix(const string & infix)
{
   string postfix;

   return postfix;
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
 * CONVERT POSTFIX TO ASSEMBLY
 * Convert postfix "5 2 +" to assembly:
 *     LOAD 5
 *     ADD 2
 *     STORE VALUE1
 **********************************************/
string convertPostfixToAssembly(const string & postfix)
{
   string assembly;

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
   }
   while (input != "quit");

}
