#ifndef PLAIN_H
#define PLAIN_H

#include "Continent.h"

typedef struct Plain Plain;

struct Plain {
    Continent base;

    int* count;
};

void initPlain(Plain* this);
void copyPlain(Plain* dest, Plain* src);
Territory* newPlain();
void disposePlain(Plain* this);

#endif /* PLAIN_H */