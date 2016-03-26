###############################################################
# Program:
#     Week 12, Hash
#     Brother Helfrich, CS235
# Author:
#     Justin Waite & Winson So
# Summary:
#     This assignment contains the hash class along with
#     an implementation of the hash using a spellchecker.
#
# Time:
#     We only spent about 4 hours total on this assignment.
#     The hardest part was researching good hashing algorithms
#     and doing different trials to see which was most
#     efficient for our use case. We ended up going with our
#     own variation of the djb2 hashing algorithm as it
#     provided the best spread for us.
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

