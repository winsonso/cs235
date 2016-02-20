###############################################################
# Program:
#     Week 07, LIST
#     Brother Helfrich, CS235
# Author:
#     Justin Waite & Winson So
# Summary:
#     This is a definition and implementation of a doubly-linked
#     list. This type of list uses Nodes that point both to the
#     next and previous nodes. The implementation provided in
#     this program is a fibonacci calculator. It will handle
# 		very large numbers due to the WholeNumber class.
# Time:
#     12 Hours. 4 Was spent chasing a bug in the WholeNumber
#     addition. Fibonacci numbers worked until number 162, WholeNumber
#     it hit a very specific case that wasn't considered in the
#     original algorithm. Heads were banged on walls for a while.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: list.h week07.o fibonacci.o
	g++ -o a.out week07.o fibonacci.o
	tar -cf week07.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week07.o       : the driver program
#      fibonacci.o    : the logic for the fibonacci-generating function
#      <anything else?>
##############################################################
week07.o: list.h week07.cpp
	g++ -c week07.cpp

fibonacci.o: fibonacci.h fibonacci.cpp list.h wholenumber.h
	g++ -c fibonacci.cpp
