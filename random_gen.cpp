#include <iostream>
using namespace std;

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

void addEdges1(vertex** vertexAddresses,int numOfVertices, int degree, int weightMax){

    for (int i =0; i<numOfVertices; i++)
    {
        for (int j=0; j<degree-1; j++)
        {
            int edgeTail = rand()%numOfVertices;
            adjListNode* newNode = (adjListNode*) malloc(sizeof(adjListNode));
            newNode->node = vertexAddresses[edgeTail];
            newNode->weight = rand()%weightMax;
            newNode->next = vertexAddresses[i]->adjList;
            vertexAddresses[i]->adjList = newNode;
        }
    }

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

int main(){
    int numOfVertices = 5000;
    int degree = 6;
    int weightMax = 10;
    srand(time(nullptr));
    vertex** vertexAddresses = genGraph(numOfVertices,weightMax);
    addEdges1(vertexAddresses,numOfVertices,degree,weightMax);
    printAdjList(vertexAddresses,numOfVertices);

}