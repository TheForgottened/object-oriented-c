#include "Mountain.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count_Mountain = 1;

errcode refresh_Mountain(Territory* this, int round) {
    if (!this->isConquered(this)) {
        return UNEXPECTED;
    }

    this->incTimeConquered(this);

    if (this->getTimeConquered(this) == 3) {
        this->setProd(this, 1);
    }

    return OK;
}

Territory* clone_Mountain(Territory* this) {
    Mountain* newMountain = NULL;
    Mountain* oldMountain = (Mountain*) this;

    newMountain = malloc(sizeof(Mountain));

    if (newMountain == NULL) {
        fprintf(stderr, "Error allocating memory for territory.\n");
    }

    copyMountain(newMountain, oldMountain);

    return (Territory*) newMountain;
}

void initMountain(Mountain* this) {
    size_t size;
    char* name = NULL;

    this->count = &count_Mountain;

    size = (strlen("Mountain")
            + 11) * sizeof(char); // '\0' and 1 number

    name = malloc(size);

    if (name == NULL) {
        fprintf(stderr, "Error allocating memory for string.\n");
        return;
    }

    snprintf(name, size, "Mountain%i", (*this->count)++);

    initContinent((Continent*) this, 7, name, 1, 0);

    free(name);

    // Functions
    this->base.base.refresh = refresh_Mountain;
    this->base.base.clone = clone_Mountain;
}

void copyMountain(Mountain* dest, Mountain* src) {
    copyContinent((Continent*) dest, (Continent*) src);

    dest->count = src->count;
}

Territory* newMountain() {
    Mountain* newMountain;

    newMountain = malloc(sizeof(Mountain));

    if (newMountain == NULL) {
        fprintf(stderr, "Error allocating memory for territory.\n");
    }

    initMountain(newMountain);

    return (Territory*) newMountain;
}

void disposeMountain(Mountain* this) {
    disposeContinent((Continent*) this);
}