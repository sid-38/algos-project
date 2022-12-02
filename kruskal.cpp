
#include <iostream>
#include <tuple>
#include <limits>
#include "heapEdge.h"
#include "random_gen.h"
#include "set.h"
#include "kruskal.h"

using namespace std;


bool DFS_traversal(vertex** G, int v, int t, int* color, int* bw){
    if (v == t) return true;
    color[v] = 1;
    for(adjListNode* w = G[v]->adjList; w!=nullptr; w = w->next){
        if(color[w->node->vertexNum] == 0){
            // if(w->node->vertexNum == t){
            //     return true;
            // }
            bool destReached = DFS_traversal(G,w->node->vertexNum,t,color,bw);
            if(destReached){
                // cout << w->node->vertexNum<< "<- ";
                // cout << "bw = " << *bw << endl;
                if(w->weight < *bw){
                    *bw = w->weight;
                }
                return true;
            }
        }
    }
    color[v] = 2;
    return false;
    
}

int DFS(vertex** G, int numOfVertices, int s, int t){
    int* color = new int[numOfVertices];
    for(int i=0; i<numOfVertices; i++){
        color[i] = 0;
    }
    int bw = numeric_limits<int>::max();
    // int bw = 100;
    DFS_traversal(G,s,t,color,&bw);

    delete(color);
    // cout << s << endl;
    return bw;
}


int kruskalMST(vertex** G, int numOfVertices, int s, int t){
    // cout << "Kruskal Beginning" << endl;

    // srand(time(nullptr));
    // int numOfVertices = 20;
    // vertex** G = generateGraph(numOfVertices,20,0);
    vertex** G1 = generateEmptyGraph(numOfVertices);
    // printAdjList(G,numOfVertices);
    // cout << "Kruskal - Empty graph generated" << endl;
    heapEdge myHeap(numOfVertices*(numOfVertices-1)/2);
    // cout << "Kruskal - Created Empty Heap" << endl;

    // cout << "Kruskal - Beginning to add edges to the heap" << endl;

    for(int i=0; i<numOfVertices; i++){
        vertex* v = G[i];
        
        for(adjListNode* w = v->adjList; w!=nullptr; w=w->next){
            myHeap.insert(v->vertexNum, w->node->vertexNum, w->weight);
        }
    }

    // cout << "Kruskal - Finished adding all edges to the heap" << endl;

    // cout << "Kruskal - Calling heap sort" << endl;
    // auto [sortedHead, sortedTail, length] = myHeap.heapSort();
    tuple<int*,int*,int*,int> result = myHeap.heapSort();
    // cout << "Kruskal - Edges sorted" << endl;
    int length = get<3>(result);
    // cout << "Kruskal - Number of edges = " << length << endl;
    int* sortedHead = get<0>(result);
    int* sortedTail = get<1>(result);
    int* weights = get<2>(result);

    // for (int i=0; i<length; i++)
    // {
    //     cout << sortedHead[i] <<"-" <<sortedTail[i] <<endl;
    // }
    // cout << "Kruskal - Making the union set" << endl;
    set mySet(numOfVertices);
    for(int v=0;v<numOfVertices;v++){
        mySet.makeSet(v);
    }

    // cout << "Kruskal - Starting to iterate through all the edges" << endl;

    for(int i=0;i<length;i++){
        int ru = mySet.find(sortedHead[i]);
        int rv = mySet.find(sortedTail[i]);
        if(ru != rv){
            mySet.unionSet(ru,rv);
            addEdgeToGraph(G1,sortedHead[i],sortedTail[i],weights[i]);
        }
    }
    // cout << "MST obtained" << endl;

    // for(int i=0; i<numOfVertices; i++){
    //     cout << mySet.find(i) << endl;
    // }
// cout<< "Original Graph" << endl;
// printAdjList(G,numOfVertices);
// cout << "-------------------"<<endl<<"New Graph"<<endl;
// printAdjList(G1,numOfVertices);
// cout << "DFS traversal through the tree" << endl;

int bwresult = DFS(G1,numOfVertices,s,t);
// cout <<  "BW is " << bwresult << endl;
return bwresult;

// return(G1);
    
//  return(0);   
}


// void kruskalBW(int numOfVertices, int s , int t){

//     vertex** G = 

// }

// int main()
// {
//     // kruskalMST(5000);
//     return(0);
// }