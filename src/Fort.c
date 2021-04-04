#include "Fort.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count_Fort = 1;

Territory* clone_Fort(Territory* this) {
    Fort* newFort = NULL;
    Fort* oldFort = (Fort*) this;

    newFort = malloc(sizeof(Fort));

    if (newFort == NULL) {
        fprintf(stderr, "Error allocating memory for territory.\n");
    }

    copyFort(newFort, oldFort);

    return (Territory*) newFort;
}

void initFort(Fort* this) {
    size_t size;
    char* name = NULL;

    this->count = &count_Fort;

    size = (strlen("fort")
            + 11) * sizeof(char); // '\0' and 1 number

    name = malloc(size);

    if (name == NULL) {
        fprintf(stderr, "Error allocating memory for string.\n");
        return;
    }

    snprintf(name, size, "fort%i", (*this->count)++);

    initContinent((Continent*) this, 8, name, 0, 0);

    free(name);

    // Functions
    this->base.base.clone = clone_Fort;
}

void copyFort(Fort* dest, Fort* src) {
    copyContinent((Continent*) dest, (Continent*) src);

    dest->count = src->count;
}

Territory* newFort() {
    Fort* newFort;

    newFort = malloc(sizeof(Fort));

    if (newFort == NULL) {
        fprintf(stderr, "Error allocating memory for territory.\n");
    }

    initFort(newFort);

    return (Territory*) newFort;
}

void disposeFort(Fort* this) {
    disposeContinent((Continent*) this);
}