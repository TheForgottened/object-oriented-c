#include "Fishery.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count_Fishery = 1;

errcode refresh_Fishery(Territory* this, int round) {
    if (!this->isConquered(this)) {
        return UNEXPECTED;
    }

    this->incTimeConquered(this);

    if (round == 7 || round == 7) {
        this->setProd(this, 4);
    }

    return OK;
}

Territory* clone_Fishery(Territory* this) {
    Fishery* newFishery = NULL;
    Fishery* oldFishery = (Fishery*) this;

    newFishery = malloc(sizeof(Fishery));

    if (newFishery == NULL) {
        fprintf(stderr, "Error allocating memory for territory.\n");
    }

    copyFishery(newFishery, oldFishery);

    return (Territory*) newFishery;
}

void initFishery(Fishery* this) {
    size_t size;
    char* name = NULL;

    this->count = &count_Fishery;

    size = (strlen("fishery")
            + 11) * sizeof(char); // '\0' and 1 number

    name = malloc(size);

    if (name == NULL) {
        fprintf(stderr, "Error allocating memory for string.\n");
        return;
    }

    snprintf(name, size, "fishery%i", (*this->count)++);

    initIsland((Island*) this, 9, name, 0, 2);

    free(name);

    // Functions
    this->base.base.clone = clone_Fishery;
    this->base.base.refresh = refresh_Fishery;
}

void copyFishery(Fishery* dest, Fishery* src) {
    copyIsland((Island*) dest, (Island*) src);

    dest->count = src->count;
}

Territory* newFishery() {
    Fishery* newFishery;

    newFishery = malloc(sizeof(Fishery));

    if (newFishery == NULL) {
        fprintf(stderr, "Error allocating memory for territory.\n");
    }

    initFishery(newFishery);

    return (Territory*) newFishery;
}

void disposeFishery(Fishery* this) {
    disposeIsland((Island*) this);
}