#include<iostream>
#include <cmath>
#include "heap.h"


using namespace std;

heap::heap(int maxSize)
{
    heapSize = -1;
    data = (int*) malloc(maxSize * sizeof(int));
}

heap::~heap()
{
    free(data);
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
    if (l <= heapSize && data[l]>data[i]){
        largest = l;
    }
    else{
        largest = i;
    }
    if (r <= heapSize && data[r] > data[largest]){
        largest = r;
    }
    if (largest != i){
        int temp = data[i];
        data[i] = data[largest];
        data[largest] = temp;
        maxHeapify(largest);
    }

}

void heap::buildHeap(){
    for (int i = parent(heapSize); i>=0; i--){
        maxHeapify(i);
    }
}

void heap::insert(int x){
        if (heapSize >= maxSize) cout << "MAX SIZE EXCEEDED" << endl;
        else if (x < 0) cout << "NEGATIVE INTEGERS CANNOT BE INSERTED" << endl;
        else{
            heapSize++;
            data[heapSize] = x;
            buildHeap();
        }
    }

int heap::pop(){
    if (heapSize < 0){
        cout << "Empty heap can't be popped" << endl;
        return -1;
    }
    int return_val = data[0];
    data[0] = data[heapSize];
    heapSize--;
    maxHeapify(0);
    return return_val;
}

void heap::printHeap(){
    for(int i =0; i<=heapSize; i++)
    {
        cout << data[i] << " ";
    }
    cout << endl;
}




// int main(){

//     heap myHeap;
//     srand(time(nullptr));
//     for(int i=0; i<20; i++){
//         myHeap.insert(rand()%10);
//     }
//     myHeap.printHeap();
//     int remove = rand()%10;
//     cout << remove << endl;
//     for(int i =0; i<remove; i++){
//         myHeap.pop();
//     }
//     myHeap.printHeap();
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

// // int main(){

// //     int a[] = {3,6,4,5,1,0,9,8,7,2,12,2,45,3,54,34,23};
// //     cout << sizeof(a)/sizeof(a[0]) << endl;
// //     buildHeap(a, sizeof(a)/sizeof(a[0]));
// //     // cout << a << endl;
// //     for (int i=0; i< 10; i++){
// //         cout << a[i] << " ";
// //     }
// // }