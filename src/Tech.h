#ifndef TECH_H
#define TECH_H

#include <stdbool.h>

typedef struct Tech Tech;

struct Tech {
    char *name, *descr;
    int cost;
    bool isBought;

    //
    // Methods
    //

    char* (*getName)(Tech *);
    char* (*getDescr)(Tech *);
    int (*getCost)(Tech *);
    void (*print)(Tech *);
};

void initTech(Tech* this, char* name, int cost, char* descr);
void disposeTech(Tech* this);

#endif /* TECH_H */