#include "Save.h"

#include <stdlib.h>
#include <string.h>

void initSave(Save* this, char* name, World w, int currPhase) {
    this->name = malloc(sizeof(name) + sizeof(char));
    strcpy(this->name, name);

    // make copy of world

    this->currPhase = currPhase;
}