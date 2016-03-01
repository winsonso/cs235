/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    Justin Waite & Winson So
 * Summary:
 *    This program will implement the huffman() function
 *    This file also contains the Huffman class.
 ************************************************************************/

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <ostream>
#include "bnode.h"
#include "pair.h"
#include "list.h"

void huffman();

class Huffman {
public:
   Huffman() : pTree(NULL) {}
   Huffman(Pair<float, std::string> data);

   void add(Huffman rhs);

   void extract(List<Pair<std::string, std::string> > & codes);

   float weight();

private:
   void extract(BinaryNode<Pair<float, std::string> > * tree, List<Pair<std::string, std::string> > & codes, std::string path = "");
   BinaryNode<Pair<float, std::string> > * pTree;
};

#endif // HUFFMAN_h
