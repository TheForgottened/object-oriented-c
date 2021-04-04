#ifndef DUNE_H
#define DUNE_H

#include "Continent.h"

typedef struct Dune Dune;

struct Dune {
    Continent base;

    int* count;
};

void initDune(Dune* this);
void copyDune(Dune* dest, Dune* src);
Territory* newDune();
void disposeDune(Dune* this);

#endif /* DUNE_H */