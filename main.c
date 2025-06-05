#include <stdio.h>
#include <stdlib.h>
#include "graph/graph.h"


int main() {

    Graph* map = buildGraph("labyrinth.txt");
    
    int agents;
    printf("Choose number of agents: ");
    scanf("%d", &agents);

    

    return 0;
}