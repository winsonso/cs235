//
// Created by Justin Waite on 3/28/16.
//

#include "graph.h"
#include <string>
#include <queue>

/*
 * NON-DEFAULT CONSTRUCTOR
 * Sets the number of vertices and allocates the
 * data array.
 */
Graph::Graph(int numVertices) throw(const char*) : numVertices(numVertices)
{
}

/*
 * COPY CONSTRUCTOR
 * Constructs a graph by copying another
 */
Graph::Graph(const Graph &rhs) throw(const char*) : numVertices(rhs.numVertices)
{
   for (vector<VertexInfo>::const_iterator it = rhs.vertices.begin();
        it != rhs.vertices.end(); ++it)
   {
      vertices.push_back(*it);
   }
}

/*
 * ASSIGNMENT OPERATOR
 * Copies one graph into another
 */
Graph &Graph::operator=(const Graph &rhs) throw(const char*)
{
   numVertices = rhs.numVertices;
   vertices.clear();

   for (vector<VertexInfo>::const_iterator it = rhs.vertices.begin();
        it != rhs.vertices.end(); ++it)
   {
      vertices.push_back(*it);
   }

   return *this;
}

/*
 * IS EDGE
 * Takes two vertices as parameters. Returns true if there is an edge
 * connecting the first to the second.
 */
bool Graph::isEdge(Vertex &first, Vertex &second) const
{
   for (vector<VertexInfo>::const_iterator it = vertices.begin();
        it != vertices.end(); ++it)
   {
      if ((*it).v == first)
      {
         for (set<Vertex>::iterator vit = (*it).adjacencyList.begin();
               vit != (*it).adjacencyList.end(); ++vit)
         {
            if ((*vit) == second)
               return true;
         }
      }
   }
   return false;
}

/*
 * FIND EDGES
 * Takes a vertex as a parameter and returns the set of vertices that
 * share an edge with it.
 */
set<Vertex> Graph::findEdges(Vertex v) const
{
   set<Vertex> vSet;
   for (vector<VertexInfo>::const_iterator it = vertices.begin();
        it != vertices.end(); ++it)
   {
      if ((*it).v == v)
      {
         vSet = (*it).adjacencyList;
      }
   }
   return vSet;
}

/*
 * FIND PATH
 * Start and end vertices are passed. Returns a vector of all the
 * vertices on the shortest path between the two.
 */
vector<Vertex> Graph::findPath(Vertex start, Vertex end) const
{
   int distance = 0;
   queue<Vertex> vQueue;
   vQueue.push(start);

   set<Vertex> visited;
   visited.insert(start);

   bool foundEnd = false;
   while (!foundEnd && !vQueue.empty())
   {
      Vertex v = vQueue.front();
      vQueue.pop();
      if (v.index() > distance)
         distance++;
      set<Vertex> adjacents = findEdges(v);
      for (set<Vertex>::iterator it = adjacents.begin(); it != adjacents.end();
            ++it)
      {
         if (visited.find(*it) != visited.end())
         {

         }
      }
   }

   return vector<Vertex>();
}

/*
 * ADD
 * Takes two vertices to represent a new edge.
 */
void Graph::add(Vertex &first, Vertex &second)
{
   VertexInfo vi;
   for (vector<VertexInfo>::iterator it = vertices.begin();
        it != vertices.end(); ++it)
   {
      if ((*it).v == first)
      {
         (*it).adjacencyList.insert(second);
         return;
      }
   }

   vi.v = first;
   vi.adjacencyList.insert(second);
   vertices.push_back(vi);
}

/*
 * ADD
 * Takes a vertex and a set of vertices to create edges.
 */
void Graph::add(Vertex first, set<Vertex> vertices)
{
   for (vector<VertexInfo>::iterator it = this->vertices.begin();
        it != this->vertices.end(); ++it)
   {
      if ((*it).v == first)
      {
         for (set<Vertex>::iterator verticesIt = vertices.begin();
              verticesIt != vertices.end(); ++verticesIt)
         {
            (*it).adjacencyList.insert(*verticesIt);
         }
         return;
      }
   }

   VertexInfo vi;
   vi.v = first;
   for (set<Vertex>::iterator verticesIt = vertices.begin();
        verticesIt != vertices.end(); ++verticesIt)
   {
      vi.adjacencyList.insert(*verticesIt);
   }
   this->vertices.push_back(vi);
}
