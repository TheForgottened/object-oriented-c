#ifndef REFUGE_H
#define REFUGE_H

#include "Island.h"

typedef struct Refuge Refuge;

struct Refuge {
    Island base;

    int* count;
};

void initRefuge(Refuge* this);
void copyRefuge(Refuge* dest, Refuge* src);
Territory* newRefuge();
void disposeRefuge(Refuge* this);

#endif /* REFUGE_H */