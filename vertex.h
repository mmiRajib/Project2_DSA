//                        ITCS 6114/8114: Algorithms and Data Structures
// 					      Programming Project 2: Shortest Paths in a Network
// 					            Md Rajib, mrajib@uncc.edu

#ifndef VERTEX_H
#define VERTEX_H

#include <iostream> //for standard i/o
#include <string> //to manipulate strings
#include <list> //used for adjacency list
using namespace std;


#define INF 9999


//Define a vertex class for the vertices of the graph
class vertex
{

public:
    string name; //name of the vertex
    list<vertex*> adj; //adjacency list
    vertex* prev; //parent vertex
    double dist; //distance from the source
    bool upDownStatus; //whether the vertex is up or down
    bool isTraversed; //used for reachability

    vertex();
    vertex(string nm);
    void insertAdjacency(vertex* nbrVertex);
    void deleteAdjacency(vertex* nbrVertex);
    void markVertexUP();
    void markVertexDown();
};

//Default constructor
vertex::vertex()
{

}

//Constructor with a name input
vertex::vertex(string nm)
{
    name = nm;
    prev = NULL;
    dist = INF;
    upDownStatus = true;
    isTraversed = false;
}

//Insert a vertex into the adjacency list
void vertex::insertAdjacency(vertex* nbrVertex)
{
    //first check if it already exist in adjacency list
    list<vertex*>::iterator iVertex;
    for(iVertex = adj.begin(); iVertex != adj.end(); ++iVertex)
    {
        if((*iVertex)->name == nbrVertex->name)
            return;
    }

    //add ino the adjacency list
    adj.push_front(nbrVertex);
}


//Delete a vertex from the adjacency lis
void vertex::deleteAdjacency(vertex* nbrVertex)
{
    //check if it exist and then remove
    list<vertex*>::iterator iVertex;
    for(iVertex = adj.begin(); iVertex != adj.end();)
    {
        if((*iVertex)->name == nbrVertex->name)
        {
            // used for for loop, returns an iterator pointing to the element after the erased one
            iVertex = adj.erase(iVertex);
        }
        else
            ++iVertex;
    }

}

//Mark the vertex as UP
void vertex::markVertexUP()
{
    upDownStatus = true;
}

//Mark the vertex as Down
void vertex::markVertexDown()
{
    upDownStatus = false;
}


#endif // VERTEX_H
