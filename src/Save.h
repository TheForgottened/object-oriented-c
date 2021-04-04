#ifndef SAVE_H
#define SAVE_H

#include "World.h"

typedef struct Save Save;

struct Save {
    char* name;
    World w;
    int currPhase; // -1 -> setup; 0 -> conquista; 1 -> recolha; 2 -> compra; 3 -> eventos; 4 -> fim de jogo;
    
    //
    // Methods
    //

    char* (*getName)(Save *);
    World* (*getWorld)(Save *);
    int (*getPhase)(Save *);
};

void initSave(Save* this, char* name, World* w, int currPhase);
void disposeSave(Save* this);

#endif /* SAVE_H */