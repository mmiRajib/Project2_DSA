//                        ITCS 6114/8114: Algorithms and Data Structures
// 					      Programming Project 2: Shortest Paths in a Network
// 					            Md Rajib, mrajib@uncc.edu

#ifndef EDGE_H
#define EDGE_H


#include <iostream> //for standard i/o
#include <string> //to manipulate strings
#include "vertex.h"
using namespace std;

//Define an edge class for the edges of the graph
class edge
{
public:
    double edgeWeight;
    vertex* sourceVertex;
    vertex* destVertex;
    bool upDownStatus;

    edge();
    edge(vertex* vertex1, vertex* vertex2, double cost);
    void markEdgeUP();
    void markEdgeDown();
};



//Default constructor
edge::edge()
{

}


//Constructor with both end's vertex name
edge::edge(vertex* vertex1, vertex* vertex2, double cost)
{
    sourceVertex = vertex1;
    destVertex = vertex2;
    edgeWeight = cost;
    upDownStatus = true;
}

//mark the edge as Up
void edge::markEdgeUP()
{
    upDownStatus = true;
}


//mark the edge as Down
void edge::markEdgeDown()
{
    upDownStatus = false;
}



#endif // EDGE_H
