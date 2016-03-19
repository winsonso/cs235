###############################################################
# Program:
#     Week 11, Sorts
#     Brother Helfrich, CS235
# Author:
#     Justin Waite & Winson So
# Summary:
#     Implements 7 different sorting methods.
# Time:
#     Total time: 6 hours.
#     The first four sorting methods took only an hour to
#     complete and were fairly trivial. The heap took the
#     longest at about 2.5 hours. Determining how to structure
#     our heap class was hard, but we decided to not make
#     a copy of the array and just pull in the array by reference
#     essentially. That way we could manipulate the array without
#     having to duplicate and return a new one. Therefore, we
#     decided that a destructor would not do us any good for
#     that class because we would end up destroying the original
#     array. The quick sort was easy to make after reading
#     and following the text book. We did not finish the
#     merge sort, and determined that was the most difficult.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week11.o
	g++ -o a.out week11.o 
	tar -cf week11.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week11.o     : the driver program
##############################################################
week11.o: bnode.h bst.h stack.h week11.cpp sortValue.h \
		sortBinary.h sortInsertion.h sortHeap.h sortBubble.h \
		sortSelection.h sortMerge.h sortQuick.h heap.h
	g++ -c week11.cpp

