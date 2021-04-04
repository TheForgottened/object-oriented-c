#include "Plain.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count_Plain = 1;

errcode refresh_Plain(Territory* this, int round) {
    if (!this->isConquered(this)) {
        return UNEXPECTED;
    }

    this->incTimeConquered(this);

    if (round == 7) {
        this->setProd(this, 2);
    }

    return OK;
}

Territory* clone_Plain(Territory* this) {
    Plain* newPlain = NULL;
    Plain* oldPlain = (Plain*) this;

    newPlain = malloc(sizeof(Plain));

    if (newPlain == NULL) {
        fprintf(stderr, "Error allocating memory for territory.\n");
    }

    copyPlain(newPlain, oldPlain);

    return (Territory*) newPlain;
}

void initPlain(Plain* this) {
    size_t size;
    char* name = NULL;

    this->count = &count_Plain;

    size = (strlen("Plain")
            + 11) * sizeof(char); // '\0' and 1 number

    name = malloc(size);

    if (name == NULL) {
        fprintf(stderr, "Error allocating memory for string.\n");
        return;
    }

    snprintf(name, size, "Plain%i", (*this->count)++);

    initContinent((Continent*) this, 7, name, 1, 0);

    free(name);

    // Functions
    this->base.base.refresh = refresh_Plain;
    this->base.base.clone = clone_Plain;
}

void copyPlain(Plain* dest, Plain* src) {
    copyContinent((Continent*) dest, (Continent*) src);

    dest->count = src->count;
}

Territory* newPlain() {
    Plain* newPlain;

    newPlain = malloc(sizeof(Plain));

    if (newPlain == NULL) {
        fprintf(stderr, "Error allocating memory for territory.\n");
    }

    initPlain(newPlain);

    return (Territory*) newPlain;
}

void disposePlain(Plain* this) {
    disposeContinent((Continent*) this);
}