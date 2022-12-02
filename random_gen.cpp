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



vertex** generateEmptyGraph(int numOfVertices){
    vertex** G =(vertex**) malloc( numOfVertices * sizeof(vertex*));
    for(int i=0; i<numOfVertices; i++)
    {
        vertex* newVertex = new vertex;
        newVertex->vertexNum=i;
        G[i] = newVertex;
    }
    return G;
}

void addEdgeToGraph(vertex** G, int v, int w, int weight){
    bool alreadyExists = false;
    for(adjListNode* node = G[v]->adjList; node!=nullptr; node=node->next){
        if(node->node->vertexNum == w){
            alreadyExists = true;
            break;
        }
    }

    if(alreadyExists){
        return;
    }

    adjListNode* newEdge = new adjListNode;
    newEdge->node = G[w];
    newEdge->next = G[v]->adjList;
    newEdge->weight = weight;
    G[v]->adjList = newEdge;

    adjListNode* newEdge2 = new adjListNode;
    newEdge2->node =  G[v];
    newEdge2->next = G[w]->adjList;
    newEdge2->weight = weight;
    G[w]->adjList = newEdge2;

    return;
}

vertex** genGraph(int vertexNum, int weightMax){
    // vertex** addresses =(vertex**) malloc(vertexNum * sizeof(vertex*));

    // for (int i =0 ; i < vertexNum ; i++)
    // {
    //     vertex* a = (vertex*) malloc(sizeof(vertex));
    //     // vertex a;
    //     a->vertexNum = i;
    //     addresses[i] = a;
    // }
    

    vertex** addresses = generateEmptyGraph(vertexNum);

    // cout << "Empty graph generated" << endl;

    for (int i=0; i<vertexNum; i++)
    {
        int head = i-1;
        int tail = i;

        if (tail == 0) head = vertexNum-1;

        int weight = rand()%weightMax;
        while(weight==0){
            weight = rand()%weightMax;
        }

        addEdgeToGraph(addresses,head,tail,weight);


        // addEdgeToGraph(addresses,)

        // adjListNode
        
        // adjListNode* head = (adjListNode*) malloc(sizeof(adjListNode));
        // if (i==vertexNum)
        // {
        //     head->node = addresses[0];
        // }
        // else
        // {
        //     head->node = addresses[i];
        // }
        // int newWeight = rand()%weightMax;
        // while (newWeight == 0) {
        //     newWeight = rand()%weightMax;
        // }
        // head->weight = newWeight;
        // head->next = addresses[i-1]->adjList;
        // addresses[i-1]->adjList = head;

        // adjListNode* tail = (adjListNode*) malloc(sizeof(adjListNode));
        // if(i==0) tail->node = addresses[vertexNum-1];
        // else tail->node = addresses[i-1];

        // tail->weight = newWeight;
        // tail->next = addresses[i]->adjList;
        // addresses[i]->adjList = tail;
    }

    // cout << "Cycle made" << endl;

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
        // cout << "Avg degree = " << (float)avg_degree/degree << endl;
        float percent_degree = (float) avg_degree/degree;
        // cout << percent_degree << endl;
        // if (percent_degree == 0.250000) cout << "25 graph generation done" << endl;
        // if (percent_degree == 0.500000) cout << "50 graph generation done" << endl;
        // if (percent_degree == 0.750000) cout << "75 graph generation done" << endl;
        int head = rand()%numOfVertices;
        int tail = rand()%numOfVertices;
        while (tail == head){
            tail = rand()%numOfVertices;
        }

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
            while(weight == 0){
                weight = rand()%weightMax;
            }
        
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
    // cout << "Graph Generated" << endl;
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