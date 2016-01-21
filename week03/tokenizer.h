/***********************************************************************
* Header:
*    TOKENIZER
* Summary:
*    This contains the Tokenizer class, which parses an input string
*    into a vector of tokens. Each token can be a single character or a
*    whole word. A delimiter should be set, with a space being the
*    default.s
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
   char delim;

   // Parses an input string s into a vector of tokens.
   void tokenize(std::string s);

public:
   // Default constructor
   Tokenizer() : delim(' ') { }

   // Non-default constructor
   Tokenizer(std::string s, char delimiter);

   // Returns the vector of tokens.
   std::vector<std::string> getVector() const { return data; }
};

/******************************************************
 * NON-DEFAULT CONSTRUCTOR - takes an input string and
 * a character. The delimiter is set to the value of
 * the character, and the string gets parsed by the
 * tokenize method.
 ******************************************************/
Tokenizer :: Tokenizer(std::string s, char delimiter)
{
   delim = delimiter;
   tokenize(s);
}

/******************************************************
 * TOKENIZE - takes an input string and parses it into
 * tokens separated by the delimiter. Parenthesis will
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
      if (*c == '(' || *c == ')')
      {
         if (temp != "")
            data.push_back(temp);
         temp = "";
         data.push_back(std::string(1, *c));
      }
      else if (*c != delim)
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
