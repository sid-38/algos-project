#include <iostream>
#include "random_gen.h"
using namespace std;

struct adjListNode;

// struct vertex {
//     int vertexNum;
//     adjListNode* adjList = nullptr;
// };

// struct adjListNode {
//     vertex* node;
//     int weight = -1;
//     adjListNode* next = nullptr;
// };


vertex** genGraph(int vertexNum, int weightMax){
    vertex** addresses =(vertex**) malloc(vertexNum * sizeof(vertex*));

    for (int i =0 ; i < vertexNum ; i++)
    {
        vertex* a = (vertex*) malloc(sizeof(vertex));
        // vertex a;
        a->vertexNum = i;
        addresses[i] = a;
    }

    for (int i=1; i<=vertexNum; i++)
    {
        
        adjListNode* head = (adjListNode*) malloc(sizeof(adjListNode));
        if (i==vertexNum)
        {
            head->node = addresses[0];
        }
        else
        {
            head->node = addresses[i];
        }
        head->weight = rand()%weightMax;
        addresses[i-1]->adjList = head;
    }

    return addresses;
}

// void addEdges1(vertex** vertexAddresses,int numOfVertices, int degree, int weightMax){

//     for (int i =0; i<numOfVertices; i++)
//     {
//         for (int j=0; j<degree-1; j++)
//         {
//             int edgeTail = rand()%numOfVertices;
//             adjListNode* newNode = (adjListNode*) malloc(sizeof(adjListNode));
//             newNode->node = vertexAddresses[edgeTail];
//             newNode->weight = rand()%weightMax;
//             newNode->next = vertexAddresses[i]->adjList;
//             vertexAddresses[i]->adjList = newNode;
//         }
//     }


// }

void addEdges(vertex** vertexAddresses,int numOfVertices, int degree, int weightMax){

    float avg_degree = 2;

    while (avg_degree < degree)
    {
        int head = rand()%numOfVertices;
        int tail = rand()%numOfVertices;

        //CHECK IF THE EDGE ALREADY EXISTS
        bool alreadyExists = false;
        for(adjListNode* n = vertexAddresses[head]->adjList; n!=nullptr; n=n->next)
        {
            // cout << "(" << n->node->vertexNum << "," << n->weight <<") ";
            if (n->node->vertexNum == tail)
            {
                alreadyExists = true;
                break;
            }
        }

        if(!alreadyExists){
            int weight = rand()%weightMax;
        
            // Add head - tail edge
            adjListNode* newHeadNode = (adjListNode*) malloc(sizeof(adjListNode));
            newHeadNode->node = vertexAddresses[tail];
            newHeadNode->weight = weight;
            newHeadNode->next = vertexAddresses[head]->adjList;
            vertexAddresses[head]->adjList = newHeadNode;    

            // Add tail - head edge
            adjListNode* newTailNode = (adjListNode*) malloc(sizeof(adjListNode));
            newTailNode->node = vertexAddresses[head];
            newTailNode->weight = weight;
            newTailNode->next = vertexAddresses[tail]->adjList;
            vertexAddresses[tail]->adjList = newTailNode;    

            avg_degree += (float) 2/numOfVertices;
        }

        // cout << "Average degree = " << avg_degree << endl;
    }

    // for (int i =0; i<numOfVertices; i++)
    // {
    //     for (int j=0; j<degree-1; j++)
    //     {
    //         int edgeTail = rand()%numOfVertices;
    //         adjListNode* newNode = (adjListNode*) malloc(sizeof(adjListNode));
    //         newNode->node = vertexAddresses[edgeTail];
    //         newNode->weight = rand()%weightMax;
    //         newNode->next = vertexAddresses[i]->adjList;
    //         vertexAddresses[i]->adjList = newNode;
    //     }
    // }

}

void printAdjList(vertex** vertexAddresses, int numOfVertices){

    for (int i=0; i<numOfVertices; i++)
    {
        cout << i << "-> ";
        for(adjListNode* n = vertexAddresses[i]->adjList; n!=nullptr; n=n->next)
        {
            cout << "(" << n->node->vertexNum << "," << n->weight <<") ";
        }
        cout << endl;
    }
}

vertex** generateGraph(int numOfVertices, int weightMax, int mode){
    int degree = 6;
    if(mode == 1) degree = (int) numOfVertices/5;
    srand(time(nullptr));
    vertex** G = genGraph(numOfVertices,weightMax);
    addEdges(G,numOfVertices,degree,weightMax);
    cout << "Graph Generated" << endl;
    return G;
}

// int main(){
//     int numOfVertices = 5000;
//     int degree = 6;
//     int weightMax = 10;
//     srand(time(nullptr));
//     // float k = (float) 2/5000;
//     // cout << "K IS " << k << endl;
//     vertex** G1 = genGraph(numOfVertices,weightMax);
//     addEdges1(G1,numOfVertices,degree,weightMax);

//     vertex** G2 = genGraph(numOfVertices, weightMax);
//     addEdges1(G2,numOfVertices,numOfVertices/5, weightMax);
//     printAdjList(G2,numOfVertices);

// }