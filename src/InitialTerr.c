#include "InitialTerr.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count_InitialTerr = 1;

int getPoints_InitialTerr(Territory* this) {
    InitialTerr* ptr = (InitialTerr*) this;

    return ptr->points;
}

Territory* clone_InitialTerr(Territory* this) {
    InitialTerr* newInitialTerr = NULL;
    InitialTerr* oldInitialTerr = (InitialTerr*) this;

    newInitialTerr = malloc(sizeof(InitialTerr));

    if (newInitialTerr == NULL) {
        fprintf(stderr, "Error allocating memory for territory.\n");
    }

    copyInitialTerr(newInitialTerr, oldInitialTerr);

    return (Territory*) newInitialTerr;
}

void initInitialTerr(InitialTerr* this) {
    size_t size;
    char* name = NULL;

    this->points = 0;
    this->count = &count_InitialTerr;

    size = (strlen("initialterr")
            + 11) * sizeof(char); // '\0' and 1 number

    name = malloc(size);

    if (name == NULL) {
        fprintf(stderr, "Error allocating memory for string.\n");
        return;
    }

    snprintf(name, size, "initialterr%i", (*this->count)++);

    initContinent((Continent*) this, 9, name, 1, 1);

    free(name);

    // Functions
    this->base.base.clone = clone_InitialTerr;
    this->base.base.getPoints = getPoints_InitialTerr;
}

void copyInitialTerr(InitialTerr* dest, InitialTerr* src) {
    copyContinent((Continent*) dest, (Continent*) src);

    dest->points = src->points;
    dest->count = src->count;
}

Territory* newInitialTerr() {
    InitialTerr* newInitialTerr;

    newInitialTerr = malloc(sizeof(InitialTerr));

    if (newInitialTerr == NULL) {
        fprintf(stderr, "Error allocating memory for territory.\n");
    }

    initInitialTerr(newInitialTerr);

    return (Territory*) newInitialTerr;
}

void disposeInitialTerr(InitialTerr* this) {
    disposeContinent((Continent*) this);
}