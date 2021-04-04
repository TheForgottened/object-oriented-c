#ifndef FORT_H
#define FORT_H

#include "Continent.h"

typedef struct Fort Fort;

struct Fort {
    Continent base;

    int* count;
};

void initFort(Fort* this);
void copyFort(Fort* dest, Fort* src);
Territory* newFort();
void disposeFort(Fort* this);

#endif /* FORT_H */