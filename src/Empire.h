#ifndef EMPIRE_H
#define EMPIRE_H

#include <stdbool.h>

#include "Territory.h"
#include "Tech.h"
#include "Codes.h"

typedef struct Empire Empire;

struct Empire {
    Territory** territories;
    int nrTerritories;

    Tech** technologies;
    int nrTechnologies;

    int safe, warehouse, force;

    //
    // Methods
    //

    // Check if it's possible to add x quantities for t types
    // Types:
    // 0 - Safe
    // 1 - Warehouse
    // 2 - Military Force
    bool (*canAdd)(Empire *, int, int);

    void (*loseForce)(Empire *);

    errcode (*gather)(Empire *);
    errcode (*addGold)(Empire *, int);
    errcode (*addProduct)(Empire *, int);
    errcode (*addForce)(Empire *, int);
    errcode (*addTech)(Empire *, Tech *);

#if DEBUG
    errcode (*forceAddTech)(Empire *, Tech *);
    void (*setGold)(Empire *, int);
    void (*setProd)(Empire *, int);
#endif

    bool (*hasTech)(Empire *, char *);

    // Makes a trade (if possible)
    // Types:
    // 0 - buy gold with product
    // 1 - buy product with gold
    // 2 - buy miliray force with gold and product
    errcode (*trade)(Empire *, int);

    errcode (*addTerr)(Empire *, Territory *);

    errcode (*rmTerrStr)(Empire *, char *);
    errcode (*rmTerrPtr)(Empire *, Territory *);

    int (*getNTerr)(Empire *);
    Territory* (*getLastConquered)(Empire *);
    int (*getForce)(Empire *);
    int (*getSafe)(Empire *);
    int (*getWarehouse)(Empire *);
    int (*getTotalGoldProd)(Empire *);
    int (*getTotalProductProd)(Empire *);
    int (*getSumPointsTerr)(Empire *);
    int (*getNTech)(Empire *);
    int (*getSumPointsTech)(Empire *);

    void (*printTerritories)(Empire *);
    void (*printNameTech)(Empire *);
    void (*print)(Empire *);
};

void initEmpire(Empire* this);
void copyEmpire(Empire* dest, Empire* src);
void disposeEmpire(Empire* this);

#endif /* EMPIRE_H */