#include "Refuge.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count_Refuge = 1;

Territory* clone_Refuge(Territory* this) {
    Refuge* newRefuge = NULL;
    Refuge* oldRefuge = (Refuge*) this;

    newRefuge = malloc(sizeof(Refuge));

    if (newRefuge == NULL) {
        fprintf(stderr, "Error allocating memory for territory.\n");
    }

    copyRefuge(newRefuge, oldRefuge);

    return (Territory*) newRefuge;
}

void initRefuge(Refuge* this) {
    size_t size;
    char* name = NULL;

    this->count = &count_Refuge;

    size = (strlen("Refuge")
            + 11) * sizeof(char); // '\0' and 1 number

    name = malloc(size);

    if (name == NULL) {
        fprintf(stderr, "Error allocating memory for string.\n");
        return;
    }

    snprintf(name, size, "Refuge%i", (*this->count)++);

    initIsland((Island*) this, 9, name, 0, 2);

    free(name);

    // Functions
    this->base.base.clone = clone_Refuge;
}

void copyRefuge(Refuge* dest, Refuge* src) {
    copyIsland((Island*) dest, (Island*) src);

    dest->count = src->count;
}

Territory* newRefuge() {
    Refuge* newRefuge;

    newRefuge = malloc(sizeof(Refuge));

    if (newRefuge == NULL) {
        fprintf(stderr, "Error allocating memory for territory.\n");
    }

    initRefuge(newRefuge);

    return (Territory*) newRefuge;
}

void disposeRefuge(Refuge* this) {
    disposeIsland((Island*) this);
}