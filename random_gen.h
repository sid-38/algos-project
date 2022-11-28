#ifndef RANDOMGEN_H
#define RANDOMGEN_H

struct adjListNode;

struct vertex {
    int vertexNum;
    adjListNode* adjList = nullptr;
};

struct adjListNode {
    vertex* node;
    int weight = -1;
    adjListNode* next = nullptr;
};

vertex** genGraph(int vertexNum, int weightMax);
void addEdges(vertex** vertexAddresses,int numOfVertices, int degree, int weightMax);
vertex** generateGraph(int numOfVertices, int weightMax, int mode);
void printAdjList(vertex** vertexAddresses, int numOfVertices);
#endif