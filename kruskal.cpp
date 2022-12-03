
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
            bool destReached = DFS_traversal(G,w->node->vertexNum,t,color,bw);
            if(destReached){
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
    DFS_traversal(G,s,t,color,&bw);

    delete(color);
    return bw;
}


int kruskalBW(vertex** G, int numOfVertices, int s, int t){
    
    vertex** G1 = generateEmptyGraph(numOfVertices);

    heapEdge myHeap(numOfVertices*(numOfVertices-1)/2);

    for(int i=0; i<numOfVertices; i++){
        vertex* v = G[i];
        
        for(adjListNode* w = v->adjList; w!=nullptr; w=w->next){
            myHeap.insert(v->vertexNum, w->node->vertexNum, w->weight);
        }
    }

    tuple<int*,int*,int*,int> result = myHeap.heapSort();
    int length = get<3>(result);
    int* sortedHead = get<0>(result);
    int* sortedTail = get<1>(result);
    int* weights = get<2>(result);

    set mySet(numOfVertices);
    for(int v=0;v<numOfVertices;v++){
        mySet.makeSet(v);
    }

    for(int i=0;i<length;i++){
        int ru = mySet.find(sortedHead[i]);
        int rv = mySet.find(sortedTail[i]);
        if(ru != rv){
            mySet.unionSet(ru,rv);
            addEdgeToGraph(G1,sortedHead[i],sortedTail[i],weights[i]);
        }
    }
    
int bwresult = DFS(G1,numOfVertices,s,t);

return bwresult;

}


// int main()
// {
//     // kruskalMST(5000);
//     return(0);
// }