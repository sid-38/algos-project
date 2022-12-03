#pragma once
#include<utility>

class heapEdge
{
private:
    struct heapElement
    {
        int vertex;
        int vertexTail;
        int key;
    };
    int maxSize;
    int heapSize;
    heapElement** data;
    int parent(int i);
    int left(int i);
    int right(int i);
    void maxHeapify(int i);
    void buildHeap(int position);

public:
    heapEdge(int maxSize);
    ~heapEdge();
    void insert(int head, int tail, int key);
    std::tuple<int,int,int> pop();
    void printHeap();
    void printHeapIndex();
    void changeKey(int vertex, int newKey);
    std::tuple<int*, int*, int*, int> heapSort();
    int* sortedArrayHead;
    int* sortedArrayTail;
    int* weights;
};

