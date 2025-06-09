#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <windows.h>

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
    int minIndex = -1;  

    for (int v = 0; v < size; v++) {
        if (!visited[v] && dist[v] < min) {
            min = dist[v];
            minIndex = v;
        }
    }

    return minIndex;
}

int* dijkstra(Graph* graph, int startIndex, int goalIndex, int* pathLength) {
    int* dist = (int*)malloc(graph->nodeCount * sizeof(int));
    int* parent = (int*)malloc(graph->nodeCount * sizeof(int));
    int* visited = (int*)calloc(graph->nodeCount, sizeof(int));

    for (int i = 0; i < graph->nodeCount; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }
    dist[startIndex] = 0;

    for (int i = 0; i < graph->nodeCount; i++) {
        int u = minIndex(dist, visited, graph->nodeCount);
        if (u == -1) break;
        if (u == goalIndex) break;  

        visited[u] = 1;

   for (int v = 0; v < graph->nodeCount; v++) {
    if (!visited[v] &&
        hasEdge(graph, u, v) &&
        graph->adjList[v] != NULL &&
        dist[u] != INT_MAX) {

        if (graph->adjList[v]->obj != NULL &&
            v != startIndex &&
            v != goalIndex) {
            continue; 
        }

        if (dist[u] + 1 < dist[v]) {
            dist[v] = dist[u] + 1;
            parent[v] = u;
        }
    }
}
    }

    if (dist[goalIndex] == INT_MAX) {
        free(dist);
        free(parent);
        free(visited);
        *pathLength = 0;
        return NULL;
    }

    int capacity = graph->nodeCount;
    int* path = (int*)malloc(capacity * sizeof(int));
    int count = 0;
    for (int current = goalIndex; current != -1; current = parent[current]) {
        path[count++] = current;
    }

    for (int i = 0; i < count / 2; i++) {
        int temp = path[i];
        path[i] = path[count - 1 - i];
        path[count - 1 - i] = temp;
    }

    free(dist);
    free(parent);
    free(visited);

    *pathLength = count;
    return path;
}



void path_finding(Graph* graph, Object** agentList, int agentSize) {
    int allReached;

    while (1) {
        allReached = 0;

        for (int k = 0; k < agentSize; k++) {
            Object* currentObject = agentList[k];

            if (currentObject->currentNode->x == currentObject->toX &&
                currentObject->currentNode->y == currentObject->toY) {
                allReached++;
                continue;
            }

            int startIndex = currentObject->currentNode->index;
            int goalIndex = getIndexFromCords(graph, currentObject->toX, currentObject->toY);

            int pathLength = 0;
            int* path = dijkstra(graph, startIndex, goalIndex, &pathLength);

            if (path == NULL || pathLength < 2) {
                free(path);
                continue; 
            }

            printf("\n%s: ", currentObject->name);
            printf("%d", path[0], path[1]);
            transportNode(graph, path[0], path[1]);
            free(path);
        }

        if (allReached == agentSize)
            break;

        Sleep(1000);
        system("cls");
        printMap(graph);
    }
}
