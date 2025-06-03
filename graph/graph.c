#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


Node* initNode(int x, int y) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->x = x;
    newNode->y = y;
    newNode->next = NULL;

    return newNode;
};

Graph* initGraph(uint width, uint height) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->width = width;
    graph->height = height;
    graph->nodeCount = width * height;
    graph->adjList = (Node**) calloc(graph->nodeCount, sizeof(Node*));
    
}