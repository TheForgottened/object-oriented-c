#ifndef INITIAL_TERR_H
#define INITIAL_TERR_H

#include "Continent.h"

typedef struct InitialTerr InitialTerr;

struct InitialTerr {
    Continent base;

    int points;
    int* count;
};

void initInitialTerr(InitialTerr* this);
void copyInitialTerr(InitialTerr* dest, InitialTerr* src);
Territory* newInitialTerr();
void disposeInitialTerr(InitialTerr* this);

#endif /* INITIAL_TERR_H */