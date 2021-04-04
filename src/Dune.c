#include "Dune.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count_Dune = 1;

Territory* clone_Dune(Territory* this) {
    Dune* newDune = NULL;
    Dune* oldDune = (Dune*) this;

    newDune = malloc(sizeof(Dune));

    if (newDune == NULL) {
        fprintf(stderr, "Error allocating memory for territory.\n");
    }

    copyDune(newDune, oldDune);

    return (Territory*) newDune;
}

void initDune(Dune* this) {
    size_t size;
    char* name = NULL;

    this->count = &count_Dune;

    size = (strlen("dune")
            + 11) * sizeof(char); // '\0' and 1 number

    name = malloc(size);

    if (name == NULL) {
        fprintf(stderr, "Error allocating memory for string.\n");
        return;
    }

    snprintf(name, size, "dune%i", (*this->count)++);

    initContinent((Continent*) this, 4, name, 0, 1);

    free(name);

    // Functions
    this->base.base.clone = clone_Dune;
}

void copyDune(Dune* dest, Dune* src) {
    copyContinent((Continent*) dest, (Continent*) src);

    dest->count = src->count;
}

Territory* newDune() {
    Dune* newDune;

    newDune = malloc(sizeof(Dune));

    if (newDune == NULL) {
        fprintf(stderr, "Error allocating memory for territory.\n");
    }

    initDune(newDune);

    return (Territory*) newDune;
}

void disposeDune(Dune* this) {
    disposeContinent((Continent*) this);
}