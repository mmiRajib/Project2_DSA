
#ifndef GRAPH_H
#define GRAPH_H



#include <iostream> //for standard i/o
#include <string> //to manipulate strings
#include <list> //used for adjacency list
#include <map> //to
#include "vertex.h"
#include "edge.h"
#include "binaryheap.h"
using namespace std;

//Define a graph class for the given graph which will
//contain vertices and edges
class graph
{
public:
    map<string, vertex> vertices;//all vertices of the graph
    map<pair<string,string>, edge> edges; //all edges of the grah
    binaryHeap priorityQ; //used for shortest path priority queue

    void addEdge(string source, string dest, double cost);
    void updateEdgeCost(string source, string dest, double cost);
    void addVertex(string name);
    void deleteEdge(string source, string dest);

    void edgeUp(string source, string dest);
    void edgeDown(string source, string dest);

    void vertexUp(string name);
    void vertexDown(string name);

    void print();
    void reachable();
    void breadthFirst(string source);


    void initializeHeap();


    void initializeSingleSource(string s);
    void relax(string u, string v);
    void dijkstra(string s);
    bool findPath(string source, string dest);
    bool checkIfVertexExist(string name);
    bool checkIfEdgeExist(string source, string dest);
};

//If does not exist, add the edge
void graph::addEdge(string source, string dest, double cost)
{

    if(!checkIfEdgeExist(source,dest))
    {
        edge newEdge(&(vertices[source]),&(vertices[dest]),cost);
        edges[make_pair(source,dest)] = newEdge;
        //update adjacency list
        vertices[source].insertAdjacency(&(vertices[dest]));
    }
}

//update the edge weight
void graph::updateEdgeCost(string source, string dest, double cost)
{
    if(checkIfEdgeExist(source,dest))
    {
        edges[make_pair(source,dest)].edgeWeight = cost;
    }
    else
       cout << "Warning: Edge does not exist" << endl;
}


//delete the edge
void graph::deleteEdge(string source, string dest)
{
    if(checkIfEdgeExist(source,dest))
    {
        edges.erase(make_pair(source,dest));
        //update adjacency list
        vertices[source].deleteAdjacency(&(vertices[dest]));
    }
    else
        cout << "Warning: Edge does not exist" << endl;

}

//If edge exist, mark as down
void graph::edgeDown(string source, string dest)
{
    if(checkIfEdgeExist(source,dest))
    {
        edges[make_pair(source,dest)].markEdgeDown();
    }
    else
       cout << "Warning: Edge does not exist" << endl;

}

//If edge exist, mark as up
void graph::edgeUp(string source, string dest)
{
    if(checkIfEdgeExist(source,dest))
    {
        edges[make_pair(source,dest)].markEdgeUP();
    }
    else
       cout << "Warning: Edge does not exist" << endl;
}


//Check if the edge already exist
bool graph::checkIfEdgeExist(string source, string dest)
{

    map<pair<string,string>, edge>::iterator iEdge;
    for(iEdge = edges.begin(); iEdge != edges.end(); ++iEdge)
    {
        if(iEdge->second.sourceVertex->name == source &&
             iEdge->second.destVertex->name == dest)
            return true;
    }

    return false;

}


//If does not exist, add the vertex
void graph::addVertex(string name)
{
    if(!checkIfVertexExist(name))
    {
        vertex newVertex(name);
        vertices[name] = newVertex;
    }
}


//If exist, mark the vertex down
void graph::vertexDown(string name)
{
    if(checkIfVertexExist(name))
    {
        vertices[name].markVertexDown();
    }
    else
        cout << "Warning: Vertex does not exist" << endl;


}


//if exist, mark the vertex up
void graph::vertexUp(string name)
{
    if(checkIfVertexExist(name))
    {
        vertices[name].markVertexUP();
    }
    else
        cout << "Warning: Vertex does not exist" << endl;
}

//Check if the vertex already exist
bool graph::checkIfVertexExist(string name)
{

    map<string, vertex>::iterator iVertex;
    for(iVertex = vertices.begin(); iVertex != vertices.end(); ++iVertex)
    {
        if(iVertex->second.name == name)
            return true;
    }

    return false;

}


//Initialize the minheap
void graph::initializeHeap()
{
    //initialize the array in the heap and heap size
    priorityQ.nodes.clear();
    priorityQ.length = 0;
    priorityQ.heapSize = 0;

    //dummy node to balance array starting with index 0
    priorityQ.nodes.push_back(&(vertices.begin()->second));

    //copy all the vertices to the heap

    map<string, vertex>::iterator iVertex;
    for(iVertex = vertices.begin(); iVertex != vertices.end(); ++iVertex)
    {
        //if vertex is active then add it to the minheap
        if(iVertex->second.upDownStatus == true)
            priorityQ.nodes.push_back(&(iVertex->second));
    }

    //set the initial length
    priorityQ.heapSize = priorityQ.nodes.size() - 1;
    priorityQ.length = priorityQ.nodes.size() - 1;



    //build the heap
    buildMinHeap(&priorityQ);

}

//Initialize the source of interest
void graph::initializeSingleSource(string s)
{
    map<string, vertex>::iterator iVertex;
    for(iVertex = vertices.begin(); iVertex != vertices.end(); ++iVertex)
    {
        iVertex->second.dist = INF; //Distance is not determined/cant be determined
        iVertex->second.prev = NULL; //No paretnt node
    }

    vertices[s].dist = 0;
}


//update the distance from source to node
void graph::relax(string u, string v)
{
    if(vertices[v].dist > vertices[u].dist + edges[make_pair(u,v)].edgeWeight
            && edges[make_pair(u,v)].upDownStatus == true)
    {
        vertices[v].dist = vertices[u].dist + edges[make_pair(u,v)].edgeWeight;
        vertices[v].prev = &(vertices[u]);

    }
}

//Apply Dijkstra's algorithm to find distances from a given vertex
void graph::dijkstra(string s)
{
    if(!checkIfVertexExist(s))
    {
        cout << "Warning:: source veretx don't exist" << endl;
        return;
    }

    //Initialize the parameters
    initializeSingleSource(s);
    initializeHeap();

    //Use the min heap
    while(!isHeapEmpty(&priorityQ))
    {
        vertex* u = heapExtractMin(&priorityQ);

        list<vertex*>::iterator iVertex;
        double prevDist = 0;
        for(iVertex = u->adj.begin(); iVertex != u->adj.end(); ++iVertex)
        {
            //store current distance
            prevDist = (*iVertex)->dist;

            //update/relax distance
            if((*iVertex)->upDownStatus == true)
                relax(u->name, (*iVertex)->name);

            //find and update the position of node in priorityQ
            if(prevDist > (*iVertex)->dist)
            {
                for(int ii=1; ii <= priorityQ.heapSize; ii++)
                {
                    if(priorityQ.nodes[ii] == (*iVertex))
                        heapDecreaseKey(&priorityQ,ii,(*iVertex)->dist);
                }
            }
        }
    }
}


//For a given source and destination, find the path and print it
bool graph::findPath(string source, string dest)
{
    //Guard for invalid input
    if(!checkIfVertexExist(source))
    {
        cout << "Warning:: source veretx don't exist" << endl;
        return false;
    }
    if(!checkIfVertexExist(dest))
    {
        cout << "Warning:: dest veretx don't exist" << endl;
        return false;
    }
    dijkstra(source);

    //first check if path exist
    //if path dont exist, return false
    if(vertices[dest].dist == INF)
    {
        cout << dest << " not reahcbale" << endl;
        return false;
    }


    //get vertices in the path
    vertex* tempVertex = &(vertices[dest]);
    list<string> pathPoints;

    while(tempVertex != NULL)
    {
        pathPoints.push_front(tempVertex->name);
        tempVertex = tempVertex->prev;
    }

    //print path
    list<string>::iterator iVertex;
    for(iVertex = pathPoints.begin(); iVertex != pathPoints.end(); ++iVertex)
    {
        cout << *iVertex << " ";
    }
    cout << vertices[dest].dist << endl;
    return true;

}

//Print vertices and edges in alphabetical order
void graph::print()
{
    map<string, vertex>::iterator iVertex;
    for(iVertex = vertices.begin(); iVertex != vertices.end(); ++iVertex)
    {
        cout << iVertex->second.name << " ";
        if (iVertex->second.upDownStatus == false)
            cout << "DOWN" << endl;
        else
            cout << endl;

        //sort adjacency list
        list<string> adjList;
        list<vertex*>::iterator jVertex;
        for(jVertex = iVertex->second.adj.begin(); jVertex != iVertex->second.adj.end(); ++jVertex)
        {
            adjList.push_back((*jVertex)->name);
        }
        adjList.sort();
        list<string>::iterator adjNodeName;
        for(adjNodeName = adjList.begin(); adjNodeName != adjList.end(); ++adjNodeName)
        {
            cout << "  " << *(adjNodeName) << " ";
            cout << edges[make_pair(iVertex->second.name,*(adjNodeName))].edgeWeight << " ";
            if(edges[make_pair(iVertex->second.name,*(adjNodeName))].upDownStatus == false)
                cout << "DOWN" << endl;
            else
                cout << endl;
        }

    }

}








//************************** Graph Reachability Analysis*************************************************
//Algorithm: for each vertex apply breadth first search to find out reachable set of vertices
//Analysis: The complexity of BFS is O(V+E). Since it is run for each vertices, i.e., V times,
//          overall running time becomes O(V^2 + VE)


//print the vertices in alphabetical order + find reachable vertices for all vertices
void graph::reachable()
{
    map<string, vertex>::iterator iVertex;
    for(iVertex = vertices.begin(); iVertex != vertices.end(); ++iVertex)
    {
        if(iVertex->second.upDownStatus)
        {
            cout << iVertex->second.name << endl;
            breadthFirst(iVertex->second.name);
        }

    }

}




//From a given vertice, traverse all reachable vertices in BFS manner and print
//in alphabetical order
void graph::breadthFirst(string source)
{
    //initalize all vertices
    map<string, vertex>::iterator iVertex;
    for(iVertex = vertices.begin(); iVertex != vertices.end(); ++iVertex)
    {
        iVertex->second.isTraversed = false;
    }

    //create a queue and enter the source first
    list<vertex*> Q;
    vertices[source].isTraversed = true;
    Q.push_back(&(vertices[source]));

    //create a list to later alphabetically reorder the vertex list
    list<string> adjList;

    //search the graph in breadth first manner
    list<vertex*>::iterator jVertex;
    while(!Q.empty())
    {
        vertex* currentVertex = Q.front();
        Q.pop_front();
        if(currentVertex->upDownStatus)//if the vertex is in up status
        {
            for(jVertex = currentVertex->adj.begin(); jVertex != currentVertex->adj.end(); ++jVertex)
            {
                //check if this vertex is already traversed and updown status of vertex and edge
                if(!(*jVertex)->isTraversed && (*jVertex)->upDownStatus &&
                        edges[make_pair(currentVertex->name,(*jVertex)->name)].upDownStatus)
                {
                    (*jVertex)->isTraversed = true;
                    adjList.push_back((*jVertex)->name);
                    Q.push_back(*jVertex);
                }

            }
        }
    }

    adjList.sort();
    list<string>::iterator adjNodeName;
    for(adjNodeName = adjList.begin(); adjNodeName != adjList.end(); ++adjNodeName)
    {
        cout << "  " << *(adjNodeName) << endl;
    }


}

#endif // GRAPH_H
