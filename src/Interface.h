#ifndef INTERFACE_H
#define INTERFACE_H

typedef struct Interface Interface;

struct Interface {
    int nextPhase;

    // Functions
    void (*setNextPhase)(Interface *, int);
};

void setNextPhase(Interface * this, int a);

#endif