###############################################################
# Program:
#     Week 05, DEQUE
#     Brother Helfrich, CS235
# Author:
#     Justin Waite & Winson So
# Summary:
#     This is a project for the creation and implementation of
#     a Deque class and its methods/properties. The deque is
#     a cmobination of stack and queue whcih can access the
#     data on both sides. The implementation displayed in this
#     project is make a Now Serving system for the Linux Lab.
# Time:
#     2 hours on nowServing and 10 hours on Deque
#     Hardest Part: Nothing seemed particularly hard this time
#     around, but as usually finding little bugs took most of
#     the time.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: deque.h week05.o nowServing.o
	g++ -o a.out week05.o nowServing.o
	tar -cf week05.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week05.o       : the driver program
#      nowServing.o   : the logic for the now serving program
##############################################################
week05.o: deque.h week05.cpp
	g++ -c week05.cpp

nowServing.o: nowServing.h nowServing.cpp deque.h request.h
	g++ -c nowServing.cpp
