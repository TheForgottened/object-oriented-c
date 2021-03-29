#ifndef INTERFACE_H
#define INTERFACE_H

#include "World.h"
#include "Save.h"
#include "Command.h"

typedef struct Interface Interface;

struct Interface {
    World* w;
    Save* saves;
    int nrSaves;
    int nextPhase;
    Command commands[14];

    //
    // Functions
    //

    // 
};

void initInterface(Interface* this, World* w);

void setNextPhase(Interface* this, int a);

void defineCommands(Interface* this);

#endif /* INTERFACE_H */