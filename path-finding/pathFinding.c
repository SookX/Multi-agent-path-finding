#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

#include "../object/object.h"
#include "../graph/graph.h"

void printMap(Graph* graph) {
    printf("+");
    for (uint i = 0; i < graph->width; i++) {
        printf("-");
    }
    printf("+\n");

    for (uint y = 0; y < graph->height; y++) {
        printf("|");  

        for (uint x = 0; x < graph->width; x++) {
            int idx = -1;
            for (uint i = 0; i < graph->nodeCount; i++) {
                Node* node = graph->adjList[i];
                if (node && node->x == x && node->y == y) {
                    idx = i;
                    break;
                }
            }

            if (idx == -1) {
                printf("#");
            } else {
                Node* node = graph->adjList[idx];
                if (node->obj) {
                    printf("%c", node->obj->name[0]);
                } else {
                    printf(" ");
                }
            }
        }

        printf("|\n");  
    }

    printf("+");
    for (unsigned int i = 0; i < graph->width; i++) {
        printf("-");
    }
    printf("+\n");
}

int minIndex(int* dist, int* visited, int size) {
    int min = INT_MAX;
    int minIndex;

    for (int v = 0; v < size; v++) {
        if (!visited[v] && dist[v] < min) {
            min = dist[v];
            minIndex = v;
        }
    }

    return minIndex;
}


void path_finding(Graph* graph, Object** agentList) {
    // Run A* algorithm for each timestep t
    // If there are not confilicts continue one step ahead
    // Else, use priority indexes in hte agentList array, higher priority move first
    int* visited = (int*)calloc(graph->nodeCount, sizeof(int));
    int* dist = (int*)malloc(graph->nodeCount * sizeof(int));
    int* parent = (int*)calloc(graph->nodeCount, sizeof(int));
    
    Object* currentObject = agentList[1];
    for(int i = 0; i < graph->nodeCount; i++) {
        dist[i] = INT_MAX;
    }
    dist[agentList[1]->currentNode->index] = 0;
    for(int i = 0; i < graph->nodeCount; i++) {
        int u = minIndex(dist, visited, graph->nodeCount);
        visited[u] = 1;

        for(int v = 0; v < graph->nodeCount; v++) {
            if(!visited[v] && hasEdge(graph, u, v) && dist[u] + 1) {  // Every distance has cost of 1
                dist[v] = dist[u] + 1;
                parent[v] = u;
            }
        }
    }

    int toIndex = getIndexFromCords(graph, currentObject->toX, currentObject->toY);
    int distance = dist[toIndex];

    int* path = (int*)malloc(sizeof(int) * graph->nodeCount);
    int pathIndex = 0;
    int currentVertex = toIndex;

    while (currentVertex != currentObject->currentNode->index) {
            path[pathIndex++] = currentVertex;
            currentVertex = parent[currentVertex];
    }
    path[pathIndex++] = currentObject->currentNode->index;

    for (int j = pathIndex - 1; j > 0; j--) {
        transportNode(graph, path[j], path[j - 1]); ;
        sleep(1);
        system("clear");
        printMap(graph);
    }
    printf("\n");
    free(path);
    free(visited);
    free(parent);
 


}