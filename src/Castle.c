#include "Castle.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count_Castle = 1;

errcode refresh_Castle(Territory* this, int round) {
    if (!this->isConquered(this)) {
        return UNEXPECTED;
    }

    this->incTimeConquered(this);

    if (round == 1 || round == 7) {
        this->setProd(this, 3);
    } else if (round == 3 || round == 9) {
        this->setProd(this, 0);
    }

    return OK;
}

Territory* clone_Castle(Territory* this) {
    Castle* newCastle = NULL;
    Castle* oldCastle = (Castle*) this;

    newCastle = malloc(sizeof(Castle));

    if (newCastle == NULL) {
        fprintf(stderr, "Error allocating memory for territory.\n");
    }

    copyCastle(newCastle, oldCastle);

    return (Territory*) newCastle;
}

void initCastle(Castle* this) {
    size_t size;
    char* name = NULL;

    this->count = &count_Castle;

    size = (strlen("castle")
            + 11) * sizeof(char); // '\0' and 1 number

    name = malloc(size);

    if (name == NULL) {
        fprintf(stderr, "Error allocating memory for string.\n");
        return;
    }

    snprintf(name, size, "castle%i", (*this->count)++);

    initContinent((Continent*) this, 7, name, 1, 0);

    free(name);

    // Functions
    this->base.base.refresh = refresh_Castle;
    this->base.base.clone = clone_Castle;
}

void copyCastle(Castle* dest, Castle* src) {
    copyContinent((Continent*) dest, (Continent*) src);

    dest->count = src->count;
}

Territory* newCastle() {
    Castle* newCastle;

    newCastle = malloc(sizeof(Castle));

    if (newCastle == NULL) {
        fprintf(stderr, "Error allocating memory for territory.\n");
    }

    initCastle(newCastle);

    return (Territory*) newCastle;
}

void disposeCastle(Castle* this) {
    disposeContinent((Continent*) this);
}