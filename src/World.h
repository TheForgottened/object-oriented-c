#ifndef WORLD_H
#define WORLD_H

#include <stdbool.h>

#include "Territory.h"
#include "Castle.h"
#include "Dune.h"
#include "Fishery.h"
#include "Fort.h"
#include "Mine.h"
#include "Mountain.h"
#include "Plain.h"
#include "Refuge.h"
#include "InitialTerr.h"

#include "Tech.h"
#include "Empire.h"

#define NR_TECHNOLOGIES 5

typedef struct World World;

struct World {
    Territory** territories;
    int nrTerritories;
    Empire emp;
    int round;
    char events[4][25];
    Tech technologies[NR_TECHNOLOGIES];

    //
    // Methods
    //

    void (*endGame)(World *);
    void (*abandonedResource)(World *);
    void (*invasion)(World *);
    void (*diplomaticAlliance)(World *);

#if DEBUG
    void (*forceEndGame)(World *);
    void (*modifyGoldEmp)(World *, int);
    void (*modifyProductEmp)(World *, int);
    errcode (*giveTech)(World *, char *);
    errcode (*giveTerr)(World *, char *);
    errcode (*chooseEvent)(World *, char *);
#endif
    errcode (*doEvent)(World *, int);

    errcode (*nextRound)(World *);
    int (*getRound)(World *);
    void (*infoEndGame)(World *, char *);

    errcode (*gather)(World *);
    errcode (*conquer)(World *, char *, int *);
    errcode (*create)(World *, char *, int);
    errcode (*acquire)(World *, char *);

    bool (*hasTechTradeEmp)(World *);
    errcode (*tradeGoldEmp)(World *);
    errcode (*tradeProdEmp)(World *);
    errcode (*tradeMilitaryEmp)(World *);

    int (*getNTerr)(World *);
    int (*getForceEmp)(World *);
    int (*getSafeEmp)(World *);
    int (*getWarehouseEmp)(World *);

    errcode (*printTerrInfo)(World *, char *);
    void (*printFreeTerr)(World *);
    void (*printAvailableTech)(World *);
    void (*print)(World *);
};

void initWorld(World* this);
void copyWorld(World* dest, World* src);
void disposeWorld(World* this);

#endif /* WORLD_H */