#include "Territory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setProd_Territory(Territory* this, int n) {
    this->prodProduct = n;
}

void setGold_Territory(Territory* this, int n) {
    this->prodGold = n;
}

void incTimeConquered_Territory(Territory* this) {
    if (this->isConquered(this)) {
        (this->timeConquered)++;
    }
}

void setConquered_Territory(Territory* this, bool b) {
    this->conquered = b;
    this->timeConquered = this->conquered ? 1 : 0;
}

bool isConquered_Territory(Territory* this) {
    printf("cona tou aqui\n");
    return this->conquered;
}

int getTimeConquered_Territory(Territory* this) {
    return this->timeConquered;
}

int getGold_Territory(Territory* this) {
    return this->prodGold;
}

int getProduct_Territory(Territory* this) {
    return this->prodProduct;
}

char* getName_Territory(Territory* this) {
    return this->name;
}

int getResistance_Territory(Territory* this) {
    return this->resistance;
}

errcode refresh_Territory(Territory* this, int turn) {
    if (this->isConquered(this)) {
        (this->timeConquered)++;
    }

    return OK;
}

void print_Territory(Territory* this) {
    if (this->isConquered(this)) {
        printf("%s   |   Production: %ig - %ip   |   Resistance: %i   |   Conquered: %i rounds", this->getName(this), this->getGold(this), this->getProduct(this), this->getResistance(this), this->getTimeConquered(this));
    } else {
        printf("%s   |   Production: %ig - %ip   |   Resistance: %i", this->getName(this), this->getGold(this), this->getProduct(this), this->getResistance(this));
    }
}

void initTerritory(Territory* this, int resistance, char* name, int prodGold, int prodProduct) {
    size_t size;

    // Functions
    this->setProd = setProd_Territory;
    this->setGold = setGold_Territory;
    this->incTimeConquered = incTimeConquered_Territory;
    this->setConquered = setConquered_Territory;
    this->isConquered = isConquered_Territory;
    this->getTimeConquered = getTimeConquered_Territory;
    this->getPoints = NULL; // virtual
    this->getGold = getGold_Territory;
    this->getProduct = getProduct_Territory;
    this->getName = getName_Territory;
    this->refresh = refresh_Territory;
    this->getResistance = getResistance_Territory;
    this->clone = NULL; // virtual
    this->print = print_Territory;

    size = (strlen(name) + 1) * sizeof(char);
    this->name = malloc(size);
    strncpy(this->name, name, size);

    this->resistance = resistance;
    this->prodGold = prodGold;
    this->prodProduct = prodProduct;

    this->timeConquered = 0;
    this->isConquered = false;

    this->print(this);
}

void copyTerritory(Territory* dest, Territory* src) {
    size_t size;

    // Functions
    dest->setProd = src->setProd;
    dest->setGold = src->setGold;
    dest->incTimeConquered = src->incTimeConquered;
    dest->setConquered = src->setConquered;
    dest->isConquered = src->isConquered;
    dest->getTimeConquered = src->getTimeConquered;
    dest->getPoints = src->getPoints; // virtual
    dest->getGold = src->getGold;
    dest->getProduct = src->getProduct;
    dest->getName = src->getName;
    dest->refresh = src->refresh;
    dest->getResistance = src->getResistance;
    dest->clone = src->clone; // virtual
    dest->print = src->print;

    size = (strlen(src->getName(src)) + 1) * sizeof(char);
    dest->name = malloc(size);
    strncpy(dest->name, src->getName(src), size);

    dest->resistance = src->resistance;
    dest->prodGold = src->prodGold;
    dest->prodProduct = src->prodProduct;

    dest->timeConquered = src->timeConquered;
    dest->isConquered = src->isConquered;
}

void disposeTerritory(Territory* this) {
    free(this->name);
}