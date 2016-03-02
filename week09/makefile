###############################################################
# Program:
#     Week 09, Binary Search Tree
#     Brother Helfrich, CS265
# Author:
#     Justin Waite & Winson So
# Summary:
#     <put a description here>
# Time:
#     Monday: 1.5 hours
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
