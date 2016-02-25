###############################################################
# Program:
#     Week 08, Binary Tree
#     Brother XXXXX, CS265
# Author:
#     <your name here>
# Summary:
#     <put a description here>
# Time:
#     4.5 hours.
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
week08.o: bnode.h huffman.h week08.cpp
	g++ -c week08.cpp

huffman.o: bnode.h huffman.h huffman.cpp
	g++ -c huffman.cpp
