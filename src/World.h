#ifndef WORLD_H
#define WORLD_H

typedef struct World World;

struct World {
    int round;
};

void initWorld(World* w);

#endif /* WORLD_H */