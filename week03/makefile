###############################################################
# Program:
#     Week 03, STACK
#     Brother Helfrich, CS235
# Author:
#     Justin Waite & Winson So
# Summary:
#     This is a project for the creation and implementation of
#     a Stack class and its methods/properties. The stack
#     is a "first in, last out" paradigm. The implementation
#		displayed in this project is a conversion from infix
#     notation into postfix notation.
# Time:
#     Approximately 5 hours.
#		The most challenging part was designing a 'tokenizer' to
#     parse the input string correctly. Doing the actual
#     conversion was fairly simple for the infix to postfix as
#     soon as we had a set of rules to follow.
###############################################################

###############################################################
# The main rule
###############################################################
a.out: stack.h week03.o infix.o
	g++ -o a.out week03.o infix.o
	tar -cf week03.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week03.o       : the driver program
#      infix.o        : the logic for the infix --> postfix program
##############################################################
week03.o: stack.h infix.h week03.cpp
	g++ -c week03.cpp

infix.o: stack.h tokenizer.h infix.h infix.cpp
	g++ -c infix.cpp
