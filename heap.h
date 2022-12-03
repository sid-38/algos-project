#pragma once
class heap
{
private:
    int maxSize;
    int heapSize;


    int parent(int i);
    int left(int i);
    int right(int i);
    void maxHeapify(int i);
    void buildHeap(int position);
    int* heapIndex;

    

public:
    int* H;
    int* D;
    heap(int maxSize);
    ~heap();
    void insert(int vertex, int key);
    int pop();
    void printHeap();
    void printHeapIndex();
    void changeKey(int vertex, int newKey);
    int* heapSort();
    // void heap::heapifyBottom(int i);
    void increaseKey(int i, int key);
    // void insert2(int vertex, int key);

};

