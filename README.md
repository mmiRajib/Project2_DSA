# Project2_DSA
                        ITCS 6114/8114: Algorithms and Data Structures
 					 Programming Project 2: Shortest Paths in a Network
 					         Md Rajib, mrajib@uncc.edu


----------------------------------------------------------------------
Running the program:
to compile: 
g++ -std=c++11 vertex.h edge.h binaryheap.h graph.h main.cpp -o  graph
to run: 
./graph network.txt

----------------------------------------------------------------------
Program Design:
The program was developed in separate sections and then merged together. This involves reading the input file, 
creating the graph, creating auxiliary functions to modify the the graph (such as deleting or adding an edge) through queries, 
building the min-heap, finding out the shortest path and finally the reachability demonstration.  
Each of these parts went through independent testing and some overall testing after they were merged. 
In the end, print functions were created to display the graph, shortest path and reachable vertices in formatted manner.

Breakdown of the Files:
The project has five different files. Among them three belongs to the graph as a whole- one is for the graph class(graph.h),
one for edge class (edge.h), and one for vertex class (vertex.h). The min-heap is implemented in a separate file namely
binaryheap.h. The graph class takes vertex and edge class to create the graph. Most of the the input output is taken care of in the main.cpp file.  

Language and Compiler:
C++ language is used with c++ 11 standard in mind.  g++ compiler version was 4.8.4. 

Summary:
To check if an edge or vertex exist, it was required to traverse the set of edges or vertices which took time. Also
the reachable function is run for each node individually (using breadth first search) which took a good amount of time.

Data Structure Design:
Edges and vertices are stored in maps within the graph class. This allows faster vertex/edge access and manipulation.
To keep track of adjacent nodes, an adjacency list  of vertices is maintained. To create the priority queue a min-heap 
is built and maintained. 

----------------------------------------------------------------------
Graph Reachability Analysis
Algorithm: for each vertex apply breadth first search to find out reachable set of vertices
Analysis: The complexity of BFS is O(V+E). Since it is run for each vertices, i.e., V times,
          overall running time becomes O(V^2 + VE)
