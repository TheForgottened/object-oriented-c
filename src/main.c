#include <stdio.h>

#include "Interface.h"

int main() {
    Interface I;
    I.setNextPhase = setNextPhase;
    printf("Hello world!\n");

    I.setNextPhase(&I, 10);

    printf("nextPhase = %i\n", I.nextPhase);
    return 0;
}