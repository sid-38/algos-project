#include <iostream>
#include <chrono>

#include "random_gen.h"
#include "dijkstra.h"
#include "kruskal.h"

using namespace std;

int main(){

    srand(time(nullptr));

    int numOfVertices = 100;
    vertex** G = generateGraph(numOfVertices,100,1);
    // printAdjList(G, numOfVertices);

    auto dijkstraStart = std::chrono::high_resolution_clock::now();
    pair<int*, int*> res1 = dijkstra(G,numOfVertices,5);
    auto dijkstraStop = std::chrono::high_resolution_clock::now();
    auto dijkstraDuration = std::chrono::duration_cast<chrono::microseconds>(dijkstraStop-dijkstraStart).count();

    auto dijkstraHeapStart = std::chrono::high_resolution_clock::now();
    pair<int*, int*> res2 = dijkstraHeap(G,numOfVertices,5);
    auto dijkstraHeapStop = std::chrono::high_resolution_clock::now();
    auto dijkstraHeapDuration = std::chrono::duration_cast<chrono::microseconds>(dijkstraHeapStop-dijkstraHeapStart).count();


    int* b_width1 = res1.first;
    int* dad1 = res1.second;

    int* b_width2 = res2.first;
    int* dad2 = res2.second;

    int dest = 10;
    cout << "Dijkstra result is " << b_width1[dest] <<endl;

    cout << "Dijkstra heap result is " << b_width2[dest] <<endl;

    // for(int i = dest; i!=-1; i=dad1[i]){
    //     cout << i << "<- ";
    // }
    // cout <<endl;

    // for(int i = dest; i!=-1; i=dad2[i]){
    //     cout << i << "<- ";
    // }
    // cout <<endl;

    auto kruskalStart = std::chrono::high_resolution_clock::now();
    int kruskalRes = kruskalMST(G,numOfVertices,5,10);
    auto kruskalStop = std::chrono::high_resolution_clock::now();
    auto kruskalDuration = std::chrono::duration_cast<chrono::microseconds>(kruskalStop-kruskalStart).count();

    cout << "Kruskal result is " << kruskalRes << endl;

    cout << "Running time" << endl << "Dijkstra = " << dijkstraDuration << endl << "Dijkstra Heap = " << dijkstraHeapDuration << endl << "Kruskal = " << kruskalDuration << endl;
    return 0;
}
