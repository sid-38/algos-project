#include<iostream>
#include <cmath>
#include "heap.h"


using namespace std;

heap::heap(int size)
{
    heapSize = -1;
    maxSize = size;
    heapIndex = (int*) malloc(maxSize * sizeof(int));
    H = new int[maxSize];
    D = new int[maxSize];
}

heap::~heap()
{
    delete(H);
    delete(D);
    free(heapIndex);
    heapIndex = nullptr;
}

int heap::parent(int i){
return floor((i-1)/2);
}

int heap::left(int i){
    return 2*i + 1;
}


int heap::right(int i){
    return 2*i + 2;
}

void heap::maxHeapify(int i){
    int l = left(i);
    int r = right(i);
    int largest;
    if (l <= heapSize && D[H[l]] > D[H[i]] ){
        largest = l;
    }
    else{
        largest = i;
    }
    if (r <= heapSize && D[H[r]] > D[H[largest]]){
        largest = r;
    }
    if (largest != i){
        int temp = H[i];
        H[i] = H[largest];
        H[largest] = temp;

        heapIndex[H[i]] = i+1;
        heapIndex[H[largest]] = largest+1;
        maxHeapify(largest);
    }

}

void heap::increaseKey(int i, int key){
    if(key < D[H[i]]){
        cout << "Heap error for vertex"<< H[i] <<" - New key is smaller than current key" << key << ","<< D[H[i]] << endl;
        return;
    }
    D[H[i]] = key;
    while(i > 0 && D[H[parent(i)]] < D[H[i]]){
        int temp = H[i];
        H[i] = H[parent(i)];
        H[parent(i)] = temp;
        heapIndex[H[i]] = i+1;
        heapIndex[H[parent(i)]] = parent(i)+1;
        i = parent(i);
    }
}

// void heap::heapifyBottom(int i){
//     int l = left(i);
//     int r = right(i);
//     int largest;
//     if (l <= heapSize && D[H[l]] > D[H[i]] ){
//         largest = l;
//     }
//     else{
//         largest = i;
//     }
//     if (r <= heapSize && D[H[r]] > D[H[largest]]){
//         largest = r;
//     }
//     if (largest != i){
//         int temp = H[i];
//         H[i] = H[largest];
//         H[largest] = temp;

//         heapIndex[H[i]] = i+1;
//         heapIndex[H[largest]] = largest+1;
//         maxHeapify(largest);
//     }

// }

void heap::buildHeap(int position){
    for (int i = parent(position); i>=0; i--){
        maxHeapify(i);
    }
}

// void heap::insert(int vertex, int key){
//     // cout << "MAXSIZE = " << maxSize << endl;
//     if (heapSize >= maxSize) cout << "MAX SIZE EXCEEDED" << endl;
//     else if (key < 0) cout << "NEGATIVE INTEGERS CANNOT BE INSERTED" << endl;
//     else{
//         heapSize++;

//         H[heapSize] = vertex;
//         D[vertex] = key;

//         heapIndex[vertex] = heapSize+1;
//         buildHeap(heapSize);
//     }
// }

void heap::insert(int vertex, int key){
    if (heapSize >= maxSize) cout << "MAX SIZE EXCEEDED" << endl;
    else if (key < 0) cout << "NEGATIVE INTEGERS CANNOT BE INSERTED" << endl;
    else{
        heapSize++;
        H[heapSize] = vertex;
        D[vertex] = -10;
        heapIndex[vertex] = heapSize+1;
        increaseKey(heapSize,key);
    }
}

int heap::pop(){
    if (heapSize < 0){
        return -1;
    }
    int return_val = H[0];
    H[0] = H[heapSize];
    heapIndex[H[0]] = 1;
    heapSize--;
    maxHeapify(0);
    return return_val;
}

void heap::printHeap(){
    // cout << "Printing heap" << endl;
    // cout << "Heap size is " << heapSize << endl;
    for(int i =0; i<=heapSize; i++)
    {
        // cout << data[i]->vertex << "-"<< data[i]->key << " ";
        cout << H[i] << "-"<< D[H[i]] << " ";
    }
    cout << endl;
}

void heap::printHeapIndex(){
    for(int i=0; i<=maxSize; i++)
    {
        cout << i << "->" << heapIndex[i] << endl;
    }
}

// void heap::changeKey(int vertex, int newKey){
//     int index = heapIndex[vertex]-1;
//     D[vertex] = newKey;
//     buildHeap(index);
// }

void heap::changeKey(int vertex, int newKey){
    increaseKey(heapIndex[vertex]-1,newKey);
}

int* heap::heapSort(){
    int* sortedArray = new int[heapSize+1];
    int indexInUse = 0;

    int largest = pop();
    while (largest!=-1){
    sortedArray[indexInUse] = largest;
    indexInUse++;
    largest = pop();
    }
    return sortedArray;
}

// int main(){
//     return 0;
// }

// int main(){
//     heap myHeap(10);
//     myHeap.insert2(6,1);
//     myHeap.printHeap();
//     myHeap.printHeapIndex();

//     srand(time(nullptr));
//     for(int i=0; i<4; i++){
//         int rand_num = rand()%10;
//         cout << rand_num << endl;
//         // cout << rand_num << endl;
//         myHeap.insert(i,rand_num);
//     }
//     myHeap.printHeap();
//     myHeap.printHeapIndex();

//     myHeap.changeKey(6,5);
//     cout << "---after change key---" << endl;

//     myHeap.printHeap();
//     myHeap.printHeapIndex();



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