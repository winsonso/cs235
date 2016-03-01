###############################################################
# Program:
#     Week 08, Binary Tree
#     Brother Helfrich, CS235
# Author:
#     Justin Waite & Winson So
# Summary:
#     This project has a Binary Node class and implements The
#     idea of a binary tree using Huffman code creation.
# Time:
#     4.5 hours on bnode, 14 hours on huffman implementation.
#     First, the huffman instructions were very unclear for
#     us, even after reading the chapter and scouring The
#     forums. After we finally got it worked out, the linux
#     lab did not like it. It ran perfectly fine on our
#     macbooks but it appears the compiler on the linux lab
#     handles pointers a tad differently. That took a long Time
#     to figure out what was wrong. This was definitely a
#     challenging assignment.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week08.o huffman.o
	g++ -o a.out week08.o huffman.o
	tar -cf week08.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week08.o     : the driver program
#      huffman.o      : the logic for the huffman code program
##############################################################
week08.o: bnode.h huffman.h week08.cpp list.h
	g++ -c week08.cpp

huffman.o: bnode.h huffman.h huffman.cpp list.h
	g++ -c huffman.cpp
