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

int findLargestFringerHeap(heap* myHeap){

    return myHeap->pop();

}

//
// DIJKSTRA IMPLEMENTATION
//

pair<int*,int*> dijkstra(vertex** G, int numOfVertices, int s){

cout << "Dijkstra starting..." << endl;
cout << "Initializaion" << endl;
int status[numOfVertices] = {};
// int b_width[numOfVertices] = {};
int* b_width = new int[numOfVertices];
int* dad = new int[numOfVertices];
// int dad[numOfVertices] = {};

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
cout << largestFringer << "-" << b_width[largestFringer] << " ";

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
    cout << largestFringer << "-" << b_width[largestFringer] << " ";
    // cout << "New largest fringer is " << largestFringer << endl;
}
cout << endl;
cout << "Dijkstra finished!" << endl;

cout << "[";
for (int i =0; i<numOfVertices; i++){
    cout << b_width[i]<<" ,";
}
cout << "]"<<endl;

return pair(b_width, dad);

}

//
// DIJKSTRA HEAP IMPLEMENTATION
//

pair<int*,int*> dijkstraHeap(vertex** G, int numOfVertices, int s){

cout << "Dijkstra starting..." << endl;
cout << "Initializaion" << endl;
heap myHeap(numOfVertices);
int status[numOfVertices] = {};
// int b_width[numOfVertices] = {};
int* b_width = new int[numOfVertices];
// int dad[numOfVertices] = {};
int* dad = new int[numOfVertices];

status[s] = in_tree;
b_width[s] = numeric_limits<int>::infinity();
dad[s] = -1;

cout << "Discovering fringes from source vertex" << endl;
for(adjListNode* v = G[s]->adjList; v != nullptr; v = v->next){
    int w = v->node->vertexNum;
    int bw = v->weight;
    status[w] = fringer;
    b_width[w] = bw;
    myHeap.insert(w,bw);
    dad[w] = s;
    // cout << "Heapsize while inserting is " << myHeap.heapSize << endl;
}
// myHeap.printHeap();

cout << "Looping though largest fringers" << endl;


int largestFringer = findLargestFringerHeap(&myHeap);
cout << largestFringer << "-" << b_width[largestFringer] << " ";
// cout << "Heap size before print is " << myHeap.heapSize << endl;
// myHeap.printHeap();

while (largestFringer != -1){
    // cout << "Largest Fringer = " << largestFringer << endl;
    status[largestFringer] = in_tree;
    for(adjListNode* v = G[largestFringer]->adjList; v != nullptr; v = v->next){
        int w = v->node->vertexNum;
        if (status[w] == unseen){
            status[w] = fringer;
            dad[w] = largestFringer;
            b_width[w] = min(b_width[largestFringer], v->weight);
            myHeap.insert(w,b_width[w]);
        }
        else if(status[w]==fringer && b_width[w]<min(b_width[largestFringer],v->weight)){
            // CRITICAL POINT
            dad[w] = largestFringer;
            b_width[w] = min(b_width[largestFringer], v->weight);
            myHeap.changeKey(w,b_width[w]);
        }
        
    }
    // cout << "Status of " << largestFringer << " = " << status[largestFringer] << endl;
    largestFringer = findLargestFringerHeap(&myHeap);
    cout <<  largestFringer << "-" << b_width[largestFringer] << " ";
    // cout << "New largest fringer is " << largestFringer << endl;
}
cout << endl;

cout << "Dijkstra finished!" << endl;
return pair(b_width, dad);

}



int main(){

    // heap myHeap(5000);
    // srand(time(nullptr));
    // for(int i=0; i<20; i++){
    //     myHeap.insert(rand()%10);
    // }
    // myHeap.printHeap();
    // int remove = rand()%10;
    // cout << remove << endl;
    // for(int i =0; i<remove; i++){
    //     myHeap.pop();
    // }
    // myHeap.printHeap();

    srand(time(nullptr));

    vertex** G = generateGraph(20,100,0);
    cout << "------ GRAPH ------" << endl;
    printAdjList(G, 20);
    cout << "-------------------" << endl;
    pair<int*, int*> res1 = dijkstra(G,20,5);

    // cout << "------ GRAPH ------" << endl;
    // printAdjList(G, 20);
    // cout << "-------------------" << endl;

    // pair<int*, int*> res2 = dijkstra(G,5000,5);
    pair<int*, int*> res2 = dijkstraHeap(G,20,5);


    int* b_width1 = res1.first;
    int* dad1 = res1.second;

    int* b_width2 = res2.first;
    int* dad2 = res2.second;
    // cout << "[";
    // for (int i =0; i<20; i++){
    //     cout << b_width1[i]<<" ,";
    // }
    // cout << "]"<<endl;

    int dest = 10;
    cout << b_width1[dest] <<endl;

    cout << b_width2[dest] <<endl;

    for(int i = dest; i!=-1; i=dad1[i]){
        cout << i << "<- ";
    }
    cout <<endl;

    for(int i = dest; i!=-1; i=dad2[i]){
        cout << i << "<- ";
    }
    cout <<endl;

    // int ar[] = {3,2,1};
    // buildHeap(ar, 3);
    // cout << ar[0] << ar[1] << ar[2];
    // return 0;
}