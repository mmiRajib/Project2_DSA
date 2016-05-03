//                        ITCS 6114/8114: Algorithms and Data Structures
// 					      Programming Project 2: Shortest Paths in a Network
// 					            Md Rajib, mrajib@uncc.edu

#include <fstream> //For file manipulation
#include <sstream> //for user query segmentation
#include "graph.h"



int main(int argc, char *argv[])
{
    //Get the input filename
     if (argc != 2)
     {
         cerr << "Usage: " << argv[0] << " <file name>" << '\n';
         exit(1);
     }
     string inputFileName = argv[1];
     ifstream inputFile(inputFileName.c_str());

     //Read the file and build the graph
     string source, dest;
     double cost;
     graph myGraph;
     while(inputFile >> source >> dest >> cost)
     {
         myGraph.addVertex(source);
         myGraph.addVertex(dest);
         myGraph.addEdge(source,dest,cost);
         myGraph.addEdge(dest,source,cost);
     }



     //Get the query from the user
     string query, tempQ;
     vector<string> param;
     do
     {
         cout << "Next query," << endl;
         getline(cin,query);
         stringstream queryStream(query);
         param.clear();

         while(queryStream >> tempQ)
         {
             param.push_back(tempQ);
         }

         //Check for matching query
         if (param[0] == "addedge" && param.size() == 4)
         {
             //check and add if the vertex do not exist already
             myGraph.addVertex(param[1]);
             myGraph.addVertex(param[2]);

             //check if the edge already exist, if exist update it
             if(myGraph.checkIfEdgeExist(param[1],param[2]))
                 myGraph.updateEdgeCost(param[1],param[2],atof(param[3].c_str()));
             else
                myGraph.addEdge(param[1],param[2],atof(param[3].c_str()));
         }
         else if(param[0] == "deleteedge" && param.size() == 3)
         {
             myGraph.deleteEdge(param[1],param[2]);
         }
         else if(param[0] == "edgedown" && param.size() == 3)
         {
             myGraph.edgeDown(param[1],param[2]);
         }
         else if(param[0] == "edgeup" && param.size() == 3)
         {
             myGraph.edgeUp(param[1], param[2]);
         }
         else if(param[0] == "vertexdown" && param.size() == 2)
         {
             myGraph.vertexDown(param[1]);
         }
         else if(param[0] == "vertexup" && param.size() == 2)
         {
             myGraph.vertexUp(param[1]);
         }
         else if(param[0] == "path" && param.size() == 3)
         {
             myGraph.findPath(param[1],param[2]);

         }
         else if(param[0]=="print" && param.size() == 1)
         {
             myGraph.print();
         }
         else if(param[0] == "reachable" && param.size() == 1)
         {
             myGraph.reachable();
         }
         else
         {
             if(param[0]!= "quit")
                cout << "Enter in a valid format" << endl;
         }


     }while(query != "quit");


    return 0;
}
