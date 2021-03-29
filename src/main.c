#include <stdio.h>

#include "Interface.h"

int main() {
    setbuf(stdout, NULL);
    World w;
    initWorld(&w);

    Interface interface;
    initInterface(&interface, &w);

    printf("Hello world!\n");

    printf("nextPhase = %i\n", interface.nextPhase);
    return 0;
}