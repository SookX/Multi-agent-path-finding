#include <stdio.h>
#include <stdlib.h>
#include "graph/graph.h"
#include "object/object.h"
#include "path-finding/pathFinding.h"


int main() {

    Graph* graph = buildGraph("labyrinth.txt");
    

    // Connect agents via nodes
    // int agents;
    // printf("Choose number of agents: ");
    // scanf("%d", &agents);
// 
    // Object** agentList = (Object**)malloc(sizeof(Object*) * agents);
// 
    // for (int i = 0; i < agents; i++) {
    //     char nameBuffer[100];
    //     uint startX, startY, toX, toY;
// 
    //     printf("\nEnter agent %d's name: ", i + 1);
    //     scanf("%99s", nameBuffer);
// 
    //     printf("Enter start X and Y coordinates for agent %s: ", nameBuffer);
    //     scanf("%d %d", &startX, &startY);
    //     int startIdx = getIndexFromCords(graph, startX, startY);
    //     if (startIdx == -1) {
    //             printf("Invalid start position for agent %s at (%d,%d).\n", nameBuffer, startX, startY);
    //             i--;
    //             continue;
    //     }
    //     if(graph->adjList[startIdx]->obj != NULL) {
    //         printf("Already agent at (%d,%d).\n", startX, startY);
    //          i--;
    //         continue;
    //     }
    //     
    //     printf("Enter goal X and Y coordinates for agent %s: ", nameBuffer);
    //     scanf("%d %d", &toX, &toY);
    //     Object* agent = initObject(nameBuffer, toX, toY);
    //     agentList[i] = agent; 
    //     graph->adjList[startIdx]->obj = agent;
    //     agent->currentNode = graph->adjList[startIdx];
    //    
// 
    //     printf("Agent '%s' placed at (%d,%d), goal is (%d,%d)\n",
    //     agent->name, startX, startY, toX, toY);
    // }
    
    int agents = 3;
    Object** agentList = (Object**)malloc(sizeof(Object*) * agents);

    // Dummy agent 1
    uint startX1 = 0, startY1 = 0, toX1 = 20, toY1 =0;
    int idx1 = getIndexFromCords(graph, startX1, startY1);
    agentList[0] = initObject("A", toX1, toY1);
    agentList[0]->currentNode = graph->adjList[idx1];
    graph->adjList[idx1]->obj = agentList[0];
    printf("Agent 'A' placed at (%d,%d), goal is (%d,%d)\n", startX1, startY1, toX1, toY1);

    // Dummy agent 2
    uint startX2 = 20, startY2 = 0, toX2 = 0, toY2 = 0;
    int idx2 = getIndexFromCords(graph, startX2, startY2);
    agentList[1] = initObject("B", toX2, toY2);
    agentList[1]->currentNode = graph->adjList[idx2];
    graph->adjList[idx2]->obj = agentList[1];
    printf("Agent 'B' placed at (%d,%d), goal is (%d,%d)\n", startX2, startY2, toX2, toY2);

    // Dummy agent 3
    uint startX3 = 13, startY3 = 5, toX3 = 1, toY3 = 3;
    int idx3 = getIndexFromCords(graph, startX3, startY3);
    agentList[2] = initObject("C", toX3, toY3);
    agentList[2]->currentNode = graph->adjList[idx3];
    graph->adjList[idx3]->obj = agentList[2];
    printf("Agent 'C' placed at (%d,%d), goal is (%d,%d)\n", startX3, startY3, toX3, toY3);

    printMap(graph);

    path_finding(graph, agentList, 3);


    return 0;
}