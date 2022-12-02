#pragma once

 #define unseen 0
 #define fringer 1
 #define in_tree 2

 #include <utility>
 #include "random_gen.h"

 std::pair<int*,int*> dijkstra(vertex** G, int numOfVertices, int s);

 std::pair<int*,int*> dijkstraHeap(vertex** G, int numOfVertices, int s);
