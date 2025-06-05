#ifndef OBJECT_H
#define OBJECT_H

typedef unsigned int uint;
typedef struct Node Node;

struct Object {
    char* name;
    uint toX;
    uint toY;
    Node* currentNode;
};

typedef struct Object Object;

Object* initObject(char* name, uint toX, uint toY);

#endif