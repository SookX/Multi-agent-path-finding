#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"


Node* initNode(uint x, uint y, uint index) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->x = x;
    newNode->y = y;
    newNode->index = index;
    newNode->next = NULL;
    newNode->obj = NULL;

    return newNode;
}

Graph* initGraph(uint width, uint height, uint nodeCount) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->width = width;
    graph->height = height;
    graph->nodeCount = nodeCount; 
    graph->adjList = (Node**)calloc(width * height, sizeof(Node*));
    
    return graph;
}

void graphInfo(Graph* graph) {
    printf("Graph width: %d\n", graph->width);
    printf("Graph height: %d\n", graph->height);
    printf("Graph nodecount: %d\n", graph->nodeCount);
}

int getIndexFromCords(Graph* graph, uint x, uint y) {
    for(int i = 0; i < graph->nodeCount; i++) {
        if (graph->adjList[i] && graph->adjList[i]->x == x && graph->adjList[i]->y == y) {
            return i;
        }
    }
    return -1;
}

void printNeighbors(Graph* graph, int index) {
    if (index < 0 || index >= graph->nodeCount) {
        printf("Invalid index: %d\n", index);
        return;
    }

    Node* node = graph->adjList[index];
    if (!node) {
        printf("No node at index %d\n", index);
        return;
    }

    printf("Neighbors of node at index %d (x=%d, y=%d):\n", index, node->x, node->y);
    
    Node* neighbor = node->next;
    while (neighbor) {
        printf("Index %d (x=%d, y=%d)\n", neighbor->index, neighbor->x, neighbor->y);
        neighbor = neighbor->next;
    }
}

int is_walkable(char a) {
    return a == ' ';
}

int hasEdge(Graph* graph, int index1, int index2) {
    Node* curr = graph->adjList[index1];
    while (curr)
    {
        if(curr->index == index2) {
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}

// Later will make better
void transportNode(Graph* graph, int startNode, int toNode) {
    if (!graph || !graph->adjList ||
        !graph->adjList[startNode] || !graph->adjList[toNode]) return;

    if (hasEdge(graph, startNode, toNode) &&
        graph->adjList[startNode]->obj != NULL &&
        graph->adjList[toNode]->obj == NULL) {

        graph->adjList[toNode]->obj = graph->adjList[startNode]->obj;
        graph->adjList[startNode]->obj->currentNode = graph->adjList[toNode];
        graph->adjList[startNode]->obj = NULL;
    }
}


Graph* buildGraph(char* filename) {
    FILE *file;
    uint width = 0, height = 0;
    char buffer[MAX_WIDTH];
    int index = 0;

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Couldn't open the file");
        exit(EXIT_FAILURE);
    }

    fgets(buffer, sizeof(buffer), file);
    width = strlen(buffer) - 3;

    int numberOfNodes = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        for (int i = 0; i < width; i++) {
            if (is_walkable(buffer[i + 1])) { 
                numberOfNodes++;
            }
        }
        height++;
    }

    height--;

    Graph* graph = initGraph(width, height, numberOfNodes);

    rewind(file);
    fgets(buffer, sizeof(buffer), file);

    int idx = 0;
    int y = 0;

    while (fgets(buffer, sizeof(buffer), file) && y < height) {
        for (int x = 0; x < width; x++) {
            char cell = buffer[x + 1];  
            if (is_walkable(cell)) {
                graph->adjList[idx] = initNode(x, y, idx);
                idx++;

            }
        }
        y++;
    }
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            int dirs[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
            int currentIdx = getIndexFromCords(graph, x, y);
            if (currentIdx == -1) continue;
            for (int d = 0; d < 4; d++) {
                int nx = x + dirs[d][0];
                int ny = y + dirs[d][1];
                if (nx >= 0 && ny >= 0 && nx < width && ny < height) {
                    int neighborIdx = getIndexFromCords(graph, nx, ny);
                    if(neighborIdx != -1) {
                        Node* neighbor = initNode(nx, ny, neighborIdx);
                        neighbor->next = graph->adjList[currentIdx]->next;
                        graph->adjList[currentIdx]->next = neighbor;
                    }
                }
                }   
        }
  
    }
    fclose(file);

    return graph;
}
