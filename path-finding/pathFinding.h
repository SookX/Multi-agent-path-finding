#ifndef PATH_FINDING_H
#define PATH_FINDING_H

typedef struct Graph Graph;


void printMap(Graph* graph);
void path_finding(Graph* graph, Object** agentList,  int agentSize);

#endif