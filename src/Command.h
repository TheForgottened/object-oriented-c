#ifndef COMANDO_H
#define COMANDO_H

#include <stdbool.h>

typedef struct Command Command;

struct Command {
    char *name, *descr, *args;
    bool available;

    //
    // Methods
    //

    char* (*getName)(Command *);
    char* (*getDescr)(Command *);
    char* (*getArgs)(Command *);

    void (*setAvailability)(Command *, bool disp);
    bool (*isAvailable)(Command *);

    void (*print)(Command *);
};

void initCommand(Command* this, char* name, char* descr, char* args);
void disposeCommand(Command* this);

#endif /* COMANDO_H */