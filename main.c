#include <stdio.h>
#include <stdlib.h>
#include "graph/graph.h"
#include "object/object.h"


int main() {

    Graph* graph = buildGraph("labyrinth.txt");
    

    // Connect agents via nodes
    int agents;
    printf("Choose number of agents: ");
    scanf("%d", &agents);

    Object** agentList = (Object**)malloc(sizeof(Object*) * agents);

    for (int i = 0; i < agents; i++) {
        char nameBuffer[100];
        uint startX, startY, toX, toY;

        printf("\nEnter agent %d's name: ", i + 1);
        scanf("%99s", nameBuffer);

        printf("Enter start X and Y coordinates for agent %s: ", nameBuffer);
        scanf("%d %d", &startX, &startY);
        int startIdx = getIndexFromCords(graph, startX, startY);
        if (startIdx == -1) {
                printf("Invalid start position for agent %s at (%d,%d).\n", nameBuffer, startX, startY);
                i--;
                continue;
        }
        if(graph->adjList[startIdx]->obj != NULL) {
            printf("Already agent at (%d,%d).\n", startX, startY);
             i--;
            continue;
        }
        
        printf("Enter goal X and Y coordinates for agent %s: ", nameBuffer);
        scanf("%d %d", &toX, &toY);
        Object* agent = initObject(nameBuffer, toX, toY);
        agentList[i] = agent; 
        graph->adjList[startIdx]->obj = agent;
        agent->currentNode = graph->adjList[startIdx];
       

        printf("Agent '%s' placed at (%d,%d), goal is (%d,%d)\n",
        agent->name, startX, startY, toX, toY);
    }
    


    return 0;
}