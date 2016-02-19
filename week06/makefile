###############################################################
# Program:
#     Week 06, NODE
#     Brother Helfrich, CS235
# Author:
#     Justin Waite & Winson So
# Summary:
#     This assignment creates a node class used for linked
#     lists. A node contains data and a pointer to the next
#     node. There is an insertion sort method which sorts an
#     unordered array of data using linked lists.
# Time:
#     5 hours on Node and .5 hours on sortInsertion. The most
#     difficult part was figuring out how to change the value
#     of a given pointer from the parameters. Turns out you
#     need to pass a reference to a pointer so it doesn't make
#     a copy of the pointer.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: node.h week06.o
	g++ -o a.out week06.o
	tar -cf week06.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week06.o      : the driver program
#      <anything else?>
##############################################################
week06.o: node.h week06.cpp sortInsertion.h
	g++ -c week06.cpp
