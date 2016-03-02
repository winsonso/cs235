###############################################################
# Program:
#     Week 09, Binary Search Tree
#     Brother Helfrich, CS265
# Author:
#     Justin Waite & Winson So
# Summary:
#     This project is to create and implement a Binary Search
#     Tree data type and its iterator. The tricky thing about
#     this project is the iterator's increment and decrement
#     functions. The implementation is a sort function using
#     a binary tree which is very trivial.
# Time:
#     bst.h required only 5 hours to complete, sortBinary.h
#     took a whole 15 minutes. The most difficult part of The
#     assignment was understanding what the decrement iterator
#     actually did and how to replicate it for the increment.
#     It took a lot of thought to fully understand how the
#     pointers really worked, but once we thought it out first,
#     implementation was easy!
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week09.o
	g++ -o a.out week09.o
	tar -cf week09.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week09.o     : the driver program
##############################################################
week09.o: bnode.h bst.h stack.h week09.cpp sortBinary.h
	g++ -c week09.cpp
