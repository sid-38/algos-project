#include<iostream>
#include <cmath>
#include "heapEdge.h"
#include <tuple>


// using namespace std;

heapEdge::heapEdge(int size)
{
    heapSize = -1;
    maxSize = size;
    data = (heapElement**) malloc(maxSize * sizeof(heapElement*));
    sortedArrayHead = nullptr;
    sortedArrayTail = nullptr;
    weights = nullptr;
    // heapIndex = (int*) malloc(maxSize * sizeof(int));
}

heapEdge::~heapEdge()
{
    for(int i=0; i<heapSize; i++){
        if(data[i]!=nullptr)
            delete(data[i]);
    }
    if (sortedArrayHead!=nullptr) delete(sortedArrayHead);
    if (sortedArrayTail!=nullptr) delete(sortedArrayTail);
    if (weights!=nullptr) delete(weights);
    free(data);
    data =  nullptr;
    // free(heapIndex);
    // heapIndex = nullptr;
}

int heapEdge::parent(int i){
return floor((i-1)/2);
}

int heapEdge::left(int i){
    return 2*i + 1;
}


int heapEdge::right(int i){
    return 2*i + 2;
}

void heapEdge::maxHeapify(int i){
    int l = left(i);
    int r = right(i);
    int largest;
    if (l <= heapSize && data[l]->key>data[i]->key){
        largest = l;
    }
    else{
        largest = i;
    }
    if (r <= heapSize && data[r]->key > data[largest]->key){
        largest = r;
    }
    if (largest != i){
        heapElement* temp = data[i];
        data[i] = data[largest];
        data[largest] = temp;
        // heapIndex[data[i]->vertex] = i+1;
        // heapIndex[data[largest]->vertex] = largest+1;
        maxHeapify(largest);
    }

}

void heapEdge::buildHeap(int position){
    for (int i = parent(position); i>=0; i--){
        maxHeapify(i);
    }
}

// void heapEdge::insert(int vertex, int key){
//     // cout << "MAXSIZE = " << maxSize << endl;
//     if (heapSize >= maxSize) cout << "MAX SIZE EXCEEDED" << endl;
//     else if (key < 0) cout << "NEGATIVE INTEGERS CANNOT BE INSERTED" << endl;
//     else{
//         heapSize++;
//         heapElement* newElement = new heapElement;
//         newElement->vertex = vertex;
//         newElement->key = key;
//         data[heapSize] = newElement;
//         heapIndex[vertex] = heapSize+1;
//         buildHeap(heapSize);
//     }
// }

void heapEdge::insert(int vertex, int tail, int key){
    // cout << "MAXSIZE = " << maxSize << endl;
    if (heapSize >= maxSize) std::cout << "MAX SIZE EXCEEDED" << std::endl;
    else if (key < 0) std::cout << "NEGATIVE INTEGERS CANNOT BE INSERTED" << std::endl;
    else{
        heapSize++;
        heapElement* newElement = new heapElement;
        // heapElement new newElement;
        newElement->vertex = vertex;
        newElement->vertexTail = tail;
        newElement->key = key;
        data[heapSize] = newElement;
        // heapIndex[vertex] = heapSize+1;
        // buildHeap(heapSize);
    }
}

std::tuple<int, int,int> heapEdge::pop(){
    if (heapSize < 0){
        // cout << "Empty heap can't be popped" << endl;
        // return std::pair(-1,-1);
        return std::make_tuple(-1,-1,-1);
    }
    std::tuple<int,int,int> return_val = std::make_tuple(data[0]->vertex,data[0]->vertexTail,data[0]->key);
    // cout << "data at 0 index accessed" << endl;
    // cout << "Heap size is " << heapSize << endl;
    // cout << "Data at heapsize is " << data[heapSize] << endl;
    data[0] = data[heapSize];
    // cout << "Data at 0 is " << data[0] << endl;
    heapSize--;
    // cout << "Heap size in pop after decrement is " << heapSize << endl;
    maxHeapify(0);
    // cout << "Heap size in pop after maxHeapify is " << heapSize << endl;
    // cout << "Popped" << endl;
    return return_val;
}

void heapEdge::printHeap(){
    // cout << "Printing heap" << endl;
    // cout << "Heap size is " << heapSize << endl;
    for(int i =0; i<=heapSize; i++)
    {
        std::cout << "(" << data[i]->vertex << "," << data[i]->vertexTail << ")-"<< data[i]->key << " ";
    }
    std::cout << std::endl;
}

// void heapEdge::printHeapIndex(){
//     for(int i=0; i<=maxSize; i++)
//     {
//         cout << i << "->" << heapIndex[i] << endl;
//     }
// }

// void heapEdge::changeKey(int vertex, int newKey){
//     int index = heapIndex[vertex]-1;
//     data[index]->key = newKey;
//     buildHeap(index);
// }

std::tuple<int*,int*,int*,int> heapEdge::heapSort(){
    sortedArrayHead = new int[heapSize+1];
    sortedArrayTail = new int[heapSize+1];
    weights = new int[heapSize+1];
    int indexInUse = 0;

    buildHeap(heapSize);

    std::tuple<int,int,int> largest = pop();
    while (std::get<0>(largest)!=-1){
    sortedArrayHead[indexInUse] = std::get<0>(largest);
    sortedArrayTail[indexInUse] = std::get<1>(largest);
    weights[indexInUse] = std::get<2>(largest);
    indexInUse++;
    largest = pop();
    }
    return std::make_tuple(sortedArrayHead,sortedArrayTail,weights,indexInUse);
}

// int main(){
//     return 0;
// }
// int main(){

//     heap myHeap(10);
//     srand(time(nullptr));
    
//     // myHeap.insert(3,1);
//     // myHeap.printHeap();
//     // myHeap.printHeapIndex();

//     for(int i=0; i<8; i++){
//         int rand_num = rand()%10;
//         // cout << rand_num << endl;
//         myHeap.insert(i,rand_num);
//     }
//     myHeap.printHeap();
//     myHeap.changeKey(5,12);
//     myHeap.printHeap();

//     cout << "Popping begins" << endl;

//     int top = myHeap.pop();
//     cout << top << endl;
//     while (top != -1){
//         top = myHeap.pop();
//         cout << top << endl;
//     }
//     // myHeap.printHeapIndex();
//     // int remove = rand()%10;
//     // cout << remove << endl;
//     // for(int i =0; i<remove; i++){
//     //     myHeap.pop();
//     // }
//     // myHeap.printHeap();


//     // heap myHeap;
//     // myHeap.insert(12);
//     // myHeap.insert(100);
//     // myHeap.insert(5);
//     // myHeap.printHeap();
//     // cout << endl;
//     // cout << myHeap.pop() << endl;
//     // myHeap.printHeap();
//     // myHeap.insert(23);
//     // // myHeap.insert(0);
//     // // myHeap.insert(12);
//     // myHeap.printHeap();
//     // // cout << endl;
//     // // cout << myHeap.pop() << endl;
//     // // myHeap.printHeap();

// }

// // // int main(){

// // //     int a[] = {3,6,4,5,1,0,9,8,7,2,12,2,45,3,54,34,23};
// // //     cout << sizeof(a)/sizeof(a[0]) << endl;
// // //     buildHeap(a, sizeof(a)/sizeof(a[0]));
// // //     // cout << a << endl;
// // //     for (int i=0; i< 10; i++){
// // //         cout << a[i] << " ";
// // //     }
// // // }