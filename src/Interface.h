#ifndef INTERFACE_H
#define INTERFACE_H

#include "World.h"
#include "Save.h"
#include "Command.h"
#include "Codes.h"

#if DEBUG
#define NR_COMMANDS 18
#else
#define NR_COMMANDS 14
#endif

typedef struct Interface Interface;

struct Interface {
    World* w;
    Save* saves;
    int nrSaves;
    int nextPhase;

    Command commands[NR_COMMANDS];

    //
    // Methods
    //

    // Prints information about the current phase
    void (*printInfoPhase)(Interface *);

    // Asks the user for commands
    errcode (*askForCommands)(Interface *);

    // Main game logic
    void (*game)(Interface *);

    errcode (*setupPhase)(Interface *);
    errcode (*conquestPhase)(Interface *);
    errcode (*gatheringPhase)(Interface *);
    errcode (*shopPhase)(Interface *);
    errcode (*eventPhase)(Interface *);

    errcode (*load)(Interface *, char *);

    // Runs the command from char[0] with its respective arguments
    errcode (*run)(Interface *, char **, int);

    // Changes the availability of the command
    errcode (*changeCMDAvailability)(Interface *, char *, bool);
};

void initInterface(Interface* this, World* w);
void disposeInterface(Interface* this);

#endif /* INTERFACE_H */