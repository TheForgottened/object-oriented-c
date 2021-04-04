#ifndef ISLAND_H
#define ISLAND_H

#include "Territory.h"

typedef struct Island Island;

struct Island {
    Territory base;
    
    int points;
};

void initIsland(Island* this, int resistance, char* name, int prodGold, int prodProduct);
void copyIsland(Island* dest, Island* src);
void disposeIsland(Island* this);

#endif /* ISLAND_H */