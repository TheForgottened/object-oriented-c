#ifndef COMANDO_H
#define COMANDO_H

#include <stdbool.h>

typedef struct Command Command;

struct Command {
    char *name, *descr, *args;
    bool available;

    char* (*getName)(Command *);
    char* (*getDescr)(Command *);
    char* (*getArgs)(Command *);

    void (*setAvailability)(Command *, bool disp);
    bool (*isAvailable)(Command *);

    char* (*getAsString)(Command *);
};

void initCommand(Command* this, char* name, char* descr, char* args);

char* getName(Command* this);
char* getDescr(Command* this);
char* getArgs(Command* this);

void setAvailability(Command* this, bool b);
bool isAvailable(Command* this);

char* getAsString(Command* this);

#endif /* COMANDO_H */