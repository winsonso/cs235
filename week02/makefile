###############################################################
# Program:
#     Week 02, SET
#     Brother Helfrich, CS235
# Author:
#     Justin Waite & Winson So
# Summary:
#     This make file builds the week02 driver and goFish game
#		to test the Set ADT.
# Time:
#     It took about 3.5 hours to complete.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week02.o goFish.o card.o
	g++ -o a.out week02.o goFish.o card.o
	tar -cf week02.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week02.o       : the driver program
#      goFish.o       : the logic for the goFish game
#      card.o         : a single playing card
##############################################################
week02.o: set.h goFish.h week02.cpp
	g++ -c week02.cpp

goFish.o: set.h goFish.h goFish.cpp card.h
	g++ -c goFish.cpp

card.o: card.h card.cpp
	g++ -c card.cpp
