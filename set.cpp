#include "set.h"



set::set(int numOfEls)
{
    numOfElements = numOfEls;
 parent = new int[numOfElements];
 rank = new int[numOfElements];

 for(int i=0; i< numOfElements; i++){
    parent[i] = -2;
    rank[i] = -2;
 }
}

set::~set()
{
    delete(parent);
    delete(rank);
}

void set::makeSet(int e){
    parent[e] = -1;
    rank[e] = 0;
}

void set::unionSet(int e1, int e2){
    if(rank[e1] > rank[e2]) parent[e2] = e1;
    else if (rank[e1] < rank[e2]) parent[e1] = e2;
    else{
        parent[e1] = e2;
        rank[e2] += 1;
    }
    // parent[e1] = e2;
}

int set::find(int e){
    int r = e;
    int* toBeMoved = new int[numOfElements];
    int index = 0;
    while(parent[r]!=-1){
        toBeMoved[index] = r;
        index++;
        r = parent[r];
    }
    toBeMoved[index] = -1;
    index = 0;
    while(toBeMoved[index]!=-1){
        parent[toBeMoved[index]] = r;
        index++;
    }
    delete(toBeMoved);
    return r;
}