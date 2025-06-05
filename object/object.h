#ifndef OBJECT_H
#include "../graph/graph.h"
#define OBJECT_H

struct Object {
    char* name;
    uint toX;
    uint toY;
};

typedef struct Object Object;

Object* initObject(char* name, uint toX, uint toY);

#endif