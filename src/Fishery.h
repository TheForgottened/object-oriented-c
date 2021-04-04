#ifndef FISHERY_H
#define FISHERY_H

#include "Island.h"

typedef struct Fishery Fishery;

struct Fishery {
    Island base;

    int* count;
};

void initFishery(Fishery* this);
void copyFishery(Fishery* dest, Fishery* src);
Territory* newFishery();
void disposeFishery(Fishery* this);

#endif /* FISHERY_H */