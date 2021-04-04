#include "Tech.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* getName_Tech(Tech* this) {
    return this->name;
}

char* getDescr_Tech(Tech* this) {
    return this->descr;
}

int getCost_Tech(Tech* this) {
    return this->cost;
}

void print_Tech(Tech* this) {
    printf("Name: %s\tCost: %i of gold\nDescription: %s", this->getName(this), this->getCost(this), this->getDescr(this));
}

void initTech(Tech* this, char* name, int cost, char* descr) {
    size_t size;

    // Functions
    this->getName = getName_Tech;
    this->getDescr = getDescr_Tech;
    this->getCost = getCost_Tech;
    this->print = print_Tech;

    size = (strlen(name) + 1) * sizeof(char);
    this->name = malloc(size);
    strncpy(this->name, name, size);

    size = (strlen(descr) + 1) * sizeof(char);
    this->descr = malloc(size);
    strncpy(this->descr, descr, size);

    this->cost = cost;
    this->isBought = false;
}

void disposeTech(Tech* this) {
    free(this->name);
    free(this->descr);
}