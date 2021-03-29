#include "Command.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void initCommand(Command* this, char* name, char* descr, char* args) {
    // Functions
    this->getName = getName;
    this->getDescr = getDescr;
    this->getArgs = getArgs;
    this->setAvailability = setAvailability;
    this->isAvailable = isAvailable;
    this->getAsString = getAsString;

    this->name = malloc((strlen(name) + 1) * sizeof(char));
    strcpy(this->name, name);

    this->descr = malloc((strlen(descr) + 1) * sizeof(char));
    strcpy(this->descr, descr);

    this->args = malloc((strlen(args) + 1) * sizeof(char));
    strcpy(this->args, args);

    this->available = 0;
}

char* getName(Command* this) {
    return this->name;
}

char* getDescr(Command* this) {
    return this->descr;
}

char* getArgs(Command* this) {
    return this->args;
}

void setAvailability(Command* this, bool b) {
    this->available = b;
}

bool isAvailable(Command* this) {
    return this->available;
}

char* getAsString(Command* this) {
    char *str = NULL;
    size_t size = strlen(this->getName(this)) 
                + strlen(this->getArgs(this)) 
                + strlen(this->getDescr(this))
                + strlen("Command:  \nAvailable: \nDescription: ")
                + 2; // '\0' and bool

    printf("\nsize_t = %li\n", size);

    str = calloc(1000 * sizeof(char), '\0');

    if (str == NULL) {
        printf("Deu merda parceiro.\n");
    }

    printf("BRUH:\nCommand: %s %s\nAvailable: %i\nDescription: %s\n", this->getName(this), this->getArgs(this), (int)this->isAvailable(this), this->getDescr(this));

    snprintf(str, 1000, "Command: %s %s\nAvailable: %i\nDescription: %s", this->getName(this), this->getArgs(this), (int)this->isAvailable(this), this->getDescr(this));
    
    return str;
}
