#ifndef MOUNTAIN_H
#define MOUNTAIN_H

#include "Continent.h"

typedef struct Mountain Mountain;

struct Mountain {
    Continent base;

    int* count;
};

void initMountain(Mountain* this);
void copyMountain(Mountain* dest, Mountain* src);
Territory* newMountain();
void disposeMountain(Mountain* this);

#endif /* MOUNTAIN_H */