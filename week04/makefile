###############################################################
# Program:
#     Week 04, QUEUE
#     Brother Helfrich, CS235
# Author:
#     Winson So & Justin Waite
# Summary:
#     This is a project for the creation and implementation of
#     a Queue class and its methods/properties. The queue
#     is a "first in, first out" paradigm. The implementation
#     displayed in this project is a program to keep track
#     of stock transactions.
# Time:
#     11 Hours (9 on Queue and 2 on stocks)
#     Most difficult part was dealing with some of the nuances
#     of the Queue class such as the advantages and
#     disadvantages of having the backNum be the index of the
#     last item or keeping a buffer at the end for the backNum.
#     For code simplicity and getting testBed to work, we went
#     with having the backNum be the actual index of the last
#     item.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: queue.h week04.o dollars.o stock.o
	g++ -o a.out week04.o dollars.o stock.o
	tar -cf week04.tar *.h *.cpp makefile

dollarsTest: dollars.o dollarsTest.cpp
	g++ -o dollarsTest dollars.o dollarsTest.cpp

##############################################################
# The individual components
#      week04.o       : the driver program
#      dollars.o      : the Dollars class
#      stock.o        : the logic for the stock program
##############################################################
week04.o: queue.h week04.cpp
	g++ -c week04.cpp

dollars.o: dollars.h dollars.cpp
	g++ -c dollars.cpp

stock.o: stock.h stock.cpp queue.h portfolio.h
	g++ -c stock.cpp
