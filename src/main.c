#include <stdio.h>

#include "Interface.h"

int main() {
    setbuf(stdout, NULL);
    World w;
    initWorld(&w);

    Interface interface;
    initInterface(&interface, &w);

    disposeInterface(&interface);
    disposeWorld(&w);
    return 0;
}