#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"

Object* initObject(char* name, uint toX, uint toY) {
    Object* obj = (Object*)malloc(sizeof(Object));
    // Check for allocation later
    strcpy(obj->name, name);
    obj->toX = toX;
    obj->toY = toY;
    return obj;
}