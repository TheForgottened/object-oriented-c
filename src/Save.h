#ifndef SAVE_H
#define SAVE_H

#include "World.h"

typedef struct Save Save;

struct Save {
    char* name;
    World w;
    int currPhase; // -1 -> setup; 0 -> conquista; 1 -> recolha; 2 -> compra; 3 -> eventos; 4 -> fim de jogo;
    
    // Returns the name of the save
    char* (*getName)(void);

    // Returns the world saved in the save
    World (*getWorld)(void);

    // Returns the phase saved in the save
    int (*getPhase)(void);
};

void initSave(Save* this, char* name, World w, int currPhase);

#endif /* SAVE_H */