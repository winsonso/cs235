/***********************************************************************
* Header:
*    INFIX
* Summary:
*    This will contain the prototype for the convertInfixToPostfix()
*    function as well as functions used in infix.cpp
* Author
*    Justin Waite & Winson So
************************************************************************/

#ifndef INFIX_H
#define INFIX_H

/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix();

/*****************************************************
 * IS OPERATOR
 * Evaluates a given string to determine if it is an
 * operator.
 *****************************************************/
bool isOperator(std::string s);

/*****************************************************
 * COMPARE OPERATORS
 * Compares two operators to determine which one is
 * of greatest precedence. Returns 1 if lhs is greater
 * 0 if equal and -1 if rhs is greater.
 *****************************************************/
int compareOperators(std::string lhs, std::string rhs);

/**********************************************
 * GET INSTRUCTION
 * Converts a char into an instruction string.
 **********************************************/
std::string getInstruction(char c);

/*****************************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly();

#endif // INFIX_H
