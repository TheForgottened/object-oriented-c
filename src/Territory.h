#ifndef TERRITORY_H
#define TERRITORY_H

#include <stdbool.h>

#include "Codes.h"

typedef struct Territory Territory;

struct Territory {
    char* name;
    int resistance;
    int prodProduct, prodGold, timeConquered;
    bool conquered;

    //
    // Methods
    //

    void (*setProd)(Territory *, int);
    void (*setGold)(Territory *, int);

    void (*incTimeConquered)(Territory *);

    void (*setConquered)(Territory *, bool);
    bool (*isConquered)(Territory *);

    int (*getTimeConquered)(Territory *);
    int (*getPoints)(Territory *); // virtual
    int (*getGold)(Territory *);
    int (*getProduct)(Territory *);
    char* (*getName)(Territory *);
    errcode (*refresh)(Territory *, int); // virtual
    int (*getResistance)(Territory *);
    void (*print)(Territory *); // virtual

    Territory* (*clone)(Territory *); // virtual
};

void initTerritory(Territory* this, int resistance, char* name, int prodGold, int prodProduct);
void copyTerritory(Territory* dest, Territory* src);
void disposeTerritory(Territory* this);

#endif /* TERRITORY_H */