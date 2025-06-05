#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"

Object* initObject(char* name, uint toX, uint toY) {
    Object* obj = (Object*)malloc(sizeof(Object));
    obj->name = strdup(name); 
    obj->toX = toX;
    obj->toY = toY;
    obj->currentNode = NULL;
    return obj;
}