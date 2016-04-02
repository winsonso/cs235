//
// Created by Justin Waite on 3/28/16.
//

#include "graph.h"

/*
 * NON-DEFAULT CONSTRUCTOR
 * Sets the number of vertices and allocates the
 * data array.
 */
Graph::Graph(int numVertices) throw(const char*) : numVertices(numVertices)
{
     try
   {
      data = new List<Vertex>[numVertices];
   }
   catch (std::bad_alloc)
   {
      throw "Unable to allocate array.";
   }

}

/*
 * COPY CONSTRUCTOR
 * Constructs a graph by copying another
 */
Graph::Graph(const Graph &rhs) throw (const char*)
{
  numVertices = rhs.numVertices;
  try
  {
     data = new List<Vertex>[numVertices];
    for (int i = 0; i < rhs.numVertices; i++)
      data[i] = rhs.data[i];
   }
  catch (std::bad_alloc)
  {
    throw "Unable to allocate array.";
  }

}

/*
 * ASSIGNMENT OPERATOR
 * Copies one graph into another
 */
Graph &Graph::operator=(const Graph &rhs) throw (const char*)
{
    try
    {
      data = new List <Vertex>[rhs.numVertices];
    }
    catch (std::bad_alloc)
    {
      throw "Unable to allocate array.";
    }

    numVertices = rhs.numVertices;
    
    for (int i = 0; i < rhs.numVertices; ++i)
    {
      data[i] = rhs.data[i];
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
   return false;
}

/*
 * FIND EDGES
 * Takes a vertex as a parameter and returns the set of vertices that
 * share an edge with it.
 */
Set<Vertex> Graph::findEdges(Vertex v) const
{
   return Set<Vertex>();
}

/*
 * FIND PATH
 * Start and end vertices are passed. Returns a vector of all the
 * vertices on the shortest path between the two.
 */
Vector<Vertex> Graph::findPath(Vertex start, Vertex end) const
{
   return Vector<Vertex>();
}

/*
 * ADD
 * Takes two vertices to represent a new edge.
 */
void Graph::add(Vertex first, Vertex second)
{
  List<Vertex>myList;
  myList.push_back(first);
  myList.push_back(second);

  for (ListIterator<Vertex> it = myList.begin(); it != myList.end(); ++it)
  cout << *it<<endl;
}

/*
 * ADD
 * Takes a vertex and a set of vertices to create edges.
 */
void Graph::add(Vertex first, Set<Vertex> vertices)
{
  for (SetIterator<Vertex> it = vertices.begin();
       it != vertices.end(); ++it)
       {
         cout << *it<<endl;
       }
    // for (int i= 0;i< vertices.size(); i++)
    // {
    //   cout << vertices.getText[i];
    // }
}
