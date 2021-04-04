#include "Continent.h"

int getPoints_Continent(Territory* this) {
    Continent* ptr = (Continent*) this;

    return ptr->points;
}

void initContinent(Continent* this, int resistance, char* name, int prodGold, int prodProduct) {
    initTerritory((Territory*) this, resistance, name, prodGold, prodProduct);

    this->points = 2;

    this->base.getPoints = getPoints_Continent;
}

void copyContinent(Continent* dest, Continent* src) {
    copyTerritory((Territory*) dest, (Territory*) src);

    dest->points = src->points;
}

void disposeContinent(Continent* this) {
    disposeTerritory((Territory*) this);
}