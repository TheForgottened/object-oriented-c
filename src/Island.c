#include "Island.h"

int getPoints_Island(Territory* this) {
    Island* ptr = (Island*) this;

    return ptr->points;
}

void initIsland(Island* this, int resistance, char* name, int prodGold, int prodProduct) {
    initTerritory((Territory*) this, resistance, name, prodGold, prodProduct);

    this->points = 3;

    this->base.getPoints = getPoints_Island;
}

void copyIsland(Island* dest, Island* src) {
    copyTerritory((Territory*) dest, (Territory*) src);

    dest->points = src->points;
}

void disposeIsland(Island* this) {
    disposeTerritory((Territory*) this);
}