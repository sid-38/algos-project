#pragma once

class set
{
private:
    /* data */
public:
    int* parent;
    int* rank;
    int numOfEdges;
    set(int numOfElements);
    ~set();
    void makeSet(int e);
    void unionSet(int e1, int e2);
    int find(int el);

};

