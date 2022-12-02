#pragma once
class heap
{
private:
    struct heapElement
    {
        int vertex;
        int key;
    };
    int maxSize;
    int heapSize;
    heapElement** data;

    int* H;
    int* D;

    
    int parent(int i);
    int left(int i);
    int right(int i);
    void maxHeapify(int i);
    void buildHeap(int position);
    int* heapIndex;

    

public:
    heap(int maxSize);
    ~heap();
    void insert(int vertex, int key);
    // void heap::insert(int vertex, int tail, int key);
    int pop();
    void printHeap();
    void printHeapIndex();
    void changeKey(int vertex, int newKey);
    int* heapSort();


};

