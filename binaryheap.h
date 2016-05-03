//                        ITCS 6114/8114: Algorithms and Data Structures
// 					      Programming Project 2: Shortest Paths in a Network
// 					            Md Rajib, mrajib@uncc.edu

#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <iostream> //standard i/o
#include <vector> //varaible array
#include <math.h> //math functions such as pow()
#include <stdlib.h> //To throw error
#include "vertex.h"
using namespace std;

//To keep track of various heap properties
struct binaryHeap
{
    vector<vertex*> nodes;
    int heapSize = 0;
    int length = 0;
};


//Functions that were used in the heap
int parent(int i);
int left(int i);
int right(int i);
void minHeapify(binaryHeap* A, int i);
void buildMinHeap(binaryHeap* A);
void heapDecreaseKey(binaryHeap* A, int i, double key);
vertex* heapMin(binaryHeap* A);
vertex* heapExtractMin(binaryHeap* A);
bool isHeapEmpty(binaryHeap* A);

void printHeap(binaryHeap A);




//find parent of i
int parent(int i)
{
    return floor((double)i / 2.0);
}

//find left children of i
int left(int i)
{
    return 2*i;
}

//find right children of i
int right(int i)
{
    return 2*i + 1;
}


//minHeapify to restore th order of the heap
void minHeapify(binaryHeap* A, int i)
{
    int l = left(i);
    int r = right(i);
    int smallest;


    if (l <= A->heapSize && A->nodes[l]->dist < A->nodes[i]->dist)
        smallest = l;
    else
        smallest = i;

    if(r <= A->heapSize && A->nodes[r]->dist < A->nodes[smallest]->dist)
        smallest = r;



    if(smallest != i)
    {
        vertex* temp = A->nodes[i];
        A->nodes[i] = A->nodes[smallest];
        A->nodes[smallest] = temp;

        minHeapify(A,smallest);
    }

}



//build the heap
void buildMinHeap(binaryHeap* A)
{
    A->heapSize = A->length;
    for(int ii=floor((double)A->length/2.0); ii>= 1; ii--)
        minHeapify(A,ii);
}


//node with minimum key
vertex* heapMin(binaryHeap* A)
{
    return A->nodes[1];
}

//Print the heap on i/o
void printHeap(binaryHeap A)
{
    for(int ii=1; ii <= A.heapSize; ii++)
        cout << ii << " : " << A.nodes[ii]->dist << endl;

}




//extract the node with minimum key
vertex* heapExtractMin(binaryHeap* A)
{
    if(A->heapSize < 1)
    {
        cerr << "ERROR: heap underflow" << endl;
        exit(1);
    }

    vertex* min = A->nodes[1];
    A->nodes[1] = A->nodes[A->heapSize];
    A->heapSize -= 1;
    minHeapify(A,1);
    return min;
}

//decrese the value of the key and then reestablish order
void heapDecreaseKey(binaryHeap* A, int i, double key)
{
    if(key > A->nodes[i]->dist)
    {
        cerr << "ERROR: New Key is larger than current key" << endl;
        exit(1);
    }

    A->nodes[i]->dist = key;
    while(i>1 && A->nodes[parent(i)]->dist > A->nodes[i]->dist)
    {
        vertex* temp = A->nodes[i];
        A->nodes[i] = A->nodes[parent(i)];
        A->nodes[parent(i)] = temp;

        i = parent(i);
    }
}

//Check if the heap is empty
bool isHeapEmpty(binaryHeap* A)
{
    if(A->heapSize < 1)
        return true;
    else
        return false;
}

#endif // BINARYHEAP_H
