#include "Save.h"

#include <stdlib.h>
#include <string.h>

char* getName_Save(Save* this) {
    return this->name;
}

World* getWorld_Save(Save* this) {
    return &this->w;
}

int getPhase_Save(Save* this) {
    return this->currPhase;
}

void initSave(Save* this, char* name, World* w, int currPhase) {
    size_t size = 0;
    // Functions
    this->getName = getName_Save;
    this->getWorld = getWorld_Save;
    this->getPhase = getPhase_Save;

    size = (strlen(name) + 1) * sizeof(char);
    this->name = malloc(size);
    strncpy(this->name, name, size);

    copyWorld(&this->w, w);

    this->currPhase = currPhase;
}

void disposeSave(Save* this) {
    disposeWorld(&this->w);
    free(this->name);
}