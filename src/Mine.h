#ifndef MINE_H
#define MINE_H

#include "Continent.h"

typedef struct Mine Mine;

struct Mine {
    Continent base;

    int* count;
};

void initMine(Mine* this);
void copyMine(Mine* dest, Mine* src);
Territory* newMine();
void disposeMine(Mine* this);

#endif /* MINE_H */