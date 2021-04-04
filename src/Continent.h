#ifndef CONTINENT_H
#define CONTINENT_H

#include "Territory.h"

typedef struct Continent Continent;

struct Continent {
    Territory base;

    int points;
};

void initContinent(Continent* this, int resistance, char* name, int prodGold, int prodProduct);
void copyContinent(Continent* dest, Continent* src);
void disposeContinent(Continent* this);

#endif /* CONTINENT_H */