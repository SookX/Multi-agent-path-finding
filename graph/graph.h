#ifndef GRAPH_H
#define GRAPH_H
#define MAX_WIDTH 256
/* Creating the Graph structure (Adjacency List Representation) for the map */
#include "../object/object.h"

typedef unsigned int uint;

struct Node {
    uint x;
    uint y;
    uint index;
    // Object pointer (will be added later)
    Object* obj;
    struct Node* next;
};

typedef struct Node Node;

struct Graph {
    uint height;
    uint width;
    uint nodeCount;
    Node** adjList;
};
typedef struct Graph Graph;

Node* initNode(uint x, uint y, uint index);
Graph* initGraph(uint width, uint height, uint nodeCount);
void graphInfo(Graph* graph);
int getIndexFromCords(Graph* graph, uint x, uint y);


Graph* buildGraph(char* filename);

#endif