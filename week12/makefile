###############################################################
# Program:
#     Week 12, Hash
#     Brother Helfrich, CS235
# Author:
#     Justin Waite & Winson So
# Summary:
#     Implements the Hash class.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week12.o spellCheck.o
	g++ -o a.out week12.o spellCheck.o
	tar -cf week12.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week12.o     : the driver program
#      spellCheck.o   : the spell-check program and driver
##############################################################
week12.o: hash.h week12.cpp list.h
	g++ -c week12.cpp 

spellCheck.o: hash.h list.h spellCheck.h spellCheck.cpp
	g++ -c spellCheck.cpp

