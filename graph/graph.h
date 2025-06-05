#ifndef GRAPH_H
#define GRAPH_H
#define MAX_WIDTH 256

/* Creating the Graph structure (Adjacency List Representation) for the map */

typedef unsigned int uint;

struct Node {
    uint x;
    uint y;
    uint index;
    // Object pointer (will be added later)
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

Graph* buildGraph(char* filename);

#endif