###############################################################
# Program:
#     Week 13, Graph
#     Brother Helfrich, CS265
# Author:
#     Justin Waite & Winson So
# Summary:
#     Implements a graph class to solve a maze.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week13.o graph.o maze.o
	g++ -o a.out week13.o graph.o maze.o
	tar -cf week13.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week13.o     : the driver program
##############################################################
week13.o: graph.h vertex.h week13.cpp
	g++ -c week13.cpp

graph.o: graph.h vertex.h graph.cpp
	g++ -c graph.cpp

maze.o: maze.cpp maze.h vertex.h graph.h
	g++ -c maze.cpp
