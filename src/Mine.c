#include "Mine.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count_Mine = 1;

errcode refresh_Mine(Territory* this, int round) {
    if (!this->isConquered(this)) {
        return UNEXPECTED;
    }

    this->incTimeConquered(this);

    if (round == 1 || round == 7) {
        this->setGold(this, 1);
    } else if (round == 4 || round == 10) {
        this->setGold(this, 2);
    }

    return OK;
}

Territory* clone_Mine(Territory* this) {
    Mine* newMine = NULL;
    Mine* oldMine = (Mine*) this;

    newMine = malloc(sizeof(Mine));

    if (newMine == NULL) {
        fprintf(stderr, "Error allocating memory for territory.\n");
    }

    copyMine(newMine, oldMine);

    return (Territory*) newMine;
}

void initMine(Mine* this) {
    size_t size;
    char* name = NULL;

    this->count = &count_Mine;

    size = (strlen("mine")
            + 11) * sizeof(char); // '\0' and 1 number

    name = malloc(size);

    if (name == NULL) {
        fprintf(stderr, "Error allocating memory for string.\n");
        return;
    }

    snprintf(name, size, "mine%i", (*this->count)++);

    initContinent((Continent*) this, 7, name, 1, 0);

    free(name);

    // Functions
    this->base.base.refresh = refresh_Mine;
    this->base.base.clone = clone_Mine;
}

void copyMine(Mine* dest, Mine* src) {
    copyContinent((Continent*) dest, (Continent*) src);

    dest->count = src->count;
}

Territory* newMine() {
    Mine* newMine;

    newMine = malloc(sizeof(Mine));

    if (newMine == NULL) {
        fprintf(stderr, "Error allocating memory for territory.\n");
    }

    initMine(newMine);

    return (Territory*) newMine;
}

void disposeMine(Mine* this) {
    disposeContinent((Continent*) this);
}