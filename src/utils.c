#include "utils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char** splitString(char* str, char* delim, int* size) {
    char **out = NULL, **temp = NULL, *token;

    *size = 0;

    token = strtok(str, delim);

    while(token != NULL) {
        temp = realloc(out, sizeof(char*) * ((*size) + 1));

        if (temp == NULL) {
            fprintf(stderr, "Error allocating memory for string.\n");
            return NULL;
        }

        out = temp;
        out[(*size)++] = token;

        token = strtok(NULL, delim);
    }

    return out;
}

char* resetString(char* str) {
    int i;

    for (i = 0; i < strlen(str) + 1; i++) {
        str[i] = '\0';
    }

    return str;
}