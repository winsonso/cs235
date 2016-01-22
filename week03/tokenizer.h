/***********************************************************************
* Header:
*    TOKENIZER
* Summary:
*    This contains the Tokenizer class, which parses an input string
*    into a vector of tokens. Each token can be a single character or a
*    whole word. Spaces are delimiters, and operators automatically get
*    inserted into their own token.
* Author
*    Justin Waite & Winson So
************************************************************************/

#include <string>
#include <iostream>
#include <vector>

/******************************************************
 * CLASS TOKENIZER - the class definition for Tokenizer
 ******************************************************/
class Tokenizer
{
private:
   std::vector<std::string> data;

   // Parses an input string s into a vector of tokens.
   void tokenize(std::string s);
   bool isOperator(char c);

public:
   // Default constructor
   Tokenizer() { }

   // Non-default constructor
   Tokenizer(std::string s);

   // Returns the vector of tokens.
   std::vector<std::string> getVector() const { return data; }
};

/******************************************************
 * NON-DEFAULT CONSTRUCTOR - takes an input string and
 * a character. The delimiter is set to the value of
 * the character, and the string gets parsed by the
 * tokenize method.
 ******************************************************/
Tokenizer :: Tokenizer(std::string s)
{
   tokenize(s);
}

/******************************************************
 * IS OPERATOR
 * Returns true if the given char is an operator.
 ******************************************************/
bool Tokenizer :: isOperator(char c)
{
   switch (c)
   {
      case '+':
      case '-':
      case '*':
      case '/':
      case '%':
      case '^':
      case '(':
      case ')':
         return true;
   }
   return false;
}

/******************************************************
 * TOKENIZE - takes an input string and parses it into
 * tokens separated by the delimiter. Operators will
 * automatically be put into their own token.
 ******************************************************/
void Tokenizer :: tokenize(std::string s)
{
   if (!data.empty())
      data.clear();

   std::string::iterator c;
   std::string temp = "";
   char currentChar[2] = {'\0', '\0'};

   for (c = s.begin(); c != s.end(); ++c)
   {
      if (isOperator(*c))
      {
         if (temp != "")
            data.push_back(temp);
         temp = "";
         data.push_back(std::string(1, *c));
      }
      else if (*c != ' ')
      {
         currentChar[0] = *c;
         temp += currentChar;
      }
      else
      {
         if (temp != "")
         {
            data.push_back(temp);
            temp = "";
         }
      }
   }
   if (temp != "")
   {
      data.push_back(temp);
   }
}
