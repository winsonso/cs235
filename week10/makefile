###############################################################
# Program:
#     Week 10, Map
#     Brother Helfrich, CS235
# Author:
#     Justin Waite & Winson So
# Summary:
#     This assignment builds and incorporates a map to count
#     the words in a given text document. A map is a set of
#     key-value pairs implemented with a BST.
# Time:
#     8 hours was spent on the assignment, most of which was
#     creating the Map class and attempting the Red-Black
#     tree business. We only got to pass Case #3 in the
#     balancing tests. Only about 20 minutes was actually
#     spent on the wordCount.cpp. Maps are easy, Red-Black
#     trees are difficult. With more time we probably could
#     have figured them out.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week10.o wordCount.o
	g++ -o a.out week10.o wordCount.o 
	tar -cf week10.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week10.o       : the driver program
#      wordCount.o    : the wordCount() function
##############################################################
week10.o: bnode.h bst.h pair.h map.h week10.cpp
	g++ -c week10.cpp

wordCount.o: map.h wordCount.h wordCount.cpp bnode.h bst.h
	g++ -c wordCount.cpp 
