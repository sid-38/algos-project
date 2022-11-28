#ifndef HEAP_H
#define HEAP_H

class heap
{
private:
    int maxSize;
    int* data;
    int heapSize;

    int parent(int i);
    int left(int i);
    int right(int i);
    void maxHeapify(int i);
    void buildHeap();

public:
    heap(int maxSize);
    ~heap();
    void insert(int x);
    int pop();
    void printHeap();

};



#endif