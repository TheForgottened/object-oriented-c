#ifndef CASTLE_H
#define CASTLE_H

#include "Continent.h"

typedef struct Castle Castle;

struct Castle {
    Continent base;

    int* count;
};

void initCastle(Castle* this);
void copyCastle(Castle* dest, Castle* src);
Territory* newCastle();
void disposeCastle(Castle* this);

#endif /* CASTLE_H */