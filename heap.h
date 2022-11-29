#ifndef HEAP_H
#define HEAP_H

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
    int pop();
    void printHeap();
    void printHeapIndex();
    void changeKey(int vertex, int newKey);

};



#endif