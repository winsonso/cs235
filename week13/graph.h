//
// Created by Justin Waite on 3/28/16.
//

#ifndef WEEK13_GRAPH_H
#define WEEK13_GRAPH_H

#include "vertex.h"
#include "list.h"
#include "set.h"
#include "vector.h"

using namespace std;

/*
 * CLASS GRAPH
 * Holds a collection of vertices and edges.
 */
class Graph
{
public:
   // NON-DEFAULT CONSTRUCTOR
   Graph(int numVertices) throw(const char*);

   // COPY CONSTRUCTOR
   Graph(const Graph &rhs) throw(const char*);

   // DESTRUCTOR
   ~Graph()
   {

   }

   // Returns the number of vertices in the graph
   int size() const { return numVertices; }

   // Takes two vertices as parameters. Returns true if there is an edge
   // connecting the first to the second.
   bool isEdge(Vertex &first, Vertex &second) const;

   // Delete all the elements in the graph
   void clear() { }

   // Takes a vertex as a parameter and returns the set of vertices that
   // share an edge with it.
   Set<Vertex> findEdges(Vertex v) const;

   // Start and end vertices are passed. Returns a vector of all the
   // vertices on the shortest path between the two.
   Vector<Vertex> findPath(Vertex start, Vertex end) const;

   // Takes two vertices to represent a new edge.
   void add(Vertex first, Vertex second);

   // Takes a vertex and a set of vertices to create edges.
   void add(Vertex first, Set<Vertex> vertices);

   // ASSIGNMENT OPERATOR
   Graph &operator=(const Graph &rhs) throw(const char*);

private:
   int numVertices; // holds the number of vertices in the graph
   List <Vertex> * data;
};

#endif //WEEK13_GRAPH_H
