#include "Command.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* getName_Command(Command* this) {
    return this->name;
}

char* getDescr_Command(Command* this) {
    return this->descr;
}

char* getArgs_Command(Command* this) {
    return this->args;
}

void setAvailability_Command(Command* this, bool b) {
    this->available = b;
}

bool isAvailable_Command(Command* this) {
    return this->available;
}

void print_Command(Command* this) {
    printf("Command: %s %s\nAvailable: %i\nDescription: %s", 
    this->getName(this), this->getArgs(this), this->isAvailable(this), this->getDescr(this));
}

void initCommand(Command* this, char* name, char* descr, char* args) {
    size_t size;

    // Functions
    this->getName = getName_Command;
    this->getDescr = getDescr_Command;
    this->getArgs = getArgs_Command;
    this->setAvailability = setAvailability_Command;
    this->isAvailable = isAvailable_Command;
    this->print = print_Command;

    size = (strlen(name) + 1) * sizeof(char);
    this->name = malloc(size);
    strncpy(this->name, name, size);

    size = (strlen(descr) + 1) * sizeof(char);
    this->descr = malloc(size);
    strncpy(this->descr, descr, size);

    size = (strlen(args) + 1) * sizeof(char);
    this->args = malloc(size);
    strncpy(this->args, args, size);

    this->available = 0;
}

void disposeCommand(Command* this) {
    free(this->name);
    free(this->descr);
    free(this->args);
}