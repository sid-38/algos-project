#include "heap.h"
#include "random_gen.h"
#include <iostream>
#include <limits>

using namespace std;

 /* status
 unseen = 0
 fringer = 1
 in-tree = 2 */   

 #define unseen 0
 #define fringer 1
 #define in_tree 2

int findLargestFringer(int* status, int* b_width, int numOfVertices){
    int largest = -1;
    int largestBWidth = -1;
    for(int i = 0; i < numOfVertices; i++){
        if(status[i] == fringer && b_width[i] > largestBWidth){
            largestBWidth = b_width[i];
            largest = i;
        }
    }

    if (largest == -1) return -1;
    return largest;
}

pair<int*,int*> dijkstra(vertex** G, int numOfVertices, int s){

cout << "Dijkstra starting..." << endl;
cout << "Initializaion" << endl;
int status[numOfVertices] = {};
int b_width[numOfVertices] = {};
int dad[numOfVertices] = {};

status[s] = in_tree;
b_width[s] = numeric_limits<int>::infinity();
dad[s] = -1;

cout << "Discovering fringes from source vertex" << endl;
for(adjListNode* v = G[s]->adjList; v != nullptr; v = v->next){
    int w = v->node->vertexNum;
    int bw = v->weight;
    status[w] = fringer;
    b_width[w] = bw;
    dad[w] = s;
}

cout << "Looping though largest fringers" << endl;


int largestFringer = findLargestFringer(status, b_width, numOfVertices);

while (largestFringer != -1){
    // cout << "Largest Fringer = " << largestFringer << endl;
    status[largestFringer] = in_tree;
    for(adjListNode* v = G[largestFringer]->adjList; v != nullptr; v = v->next){
        int w = v->node->vertexNum;
        if (status[w] == unseen){
            status[w] = fringer;
            dad[w] = largestFringer;
            b_width[w] = min(b_width[largestFringer], v->weight);
        }
        else if(status[w]==fringer && b_width[w]<min(b_width[largestFringer],v->weight)){
            dad[w] = largestFringer;
            b_width[w] = min(b_width[largestFringer], v->weight);
        }
        
    }
    // cout << "Status of " << largestFringer << " = " << status[largestFringer] << endl;
    largestFringer = findLargestFringer(status, b_width, numOfVertices);
    // cout << "New largest fringer is " << largestFringer << endl;
}

cout << "Dijkstra finished!" << endl;
return pair(b_width, dad);

}

int main(){

    heap myHeap(5000);
    srand(time(nullptr));
    for(int i=0; i<20; i++){
        myHeap.insert(rand()%10);
    }
    myHeap.printHeap();
    int remove = rand()%10;
    cout << remove << endl;
    for(int i =0; i<remove; i++){
        myHeap.pop();
    }
    myHeap.printHeap();

    // vertex** G = generateGraph(5000,100,0);
    // pair<int*, int*> res = dijkstra(G,5000,5);
    // int* b_width = res.first;
    // int* dad = res.second;

    // int dest = 200;
    // cout << b_width[dest] <<endl;

    // for(int i = dest; i!=-1; i=dad[i]){
    //     cout << i << "<- ";
    // }
    // cout <<endl;
    // int ar[] = {3,2,1};
    // buildHeap(ar, 3);
    // cout << ar[0] << ar[1] << ar[2];
    // return 0;
}