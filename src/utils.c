#include "utils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char** splitString(char* str, char* delim, int* size) {
    char **out = NULL, **temp = NULL, *next;

    *size = 0;

    while((next = strsep(&str, delim)) != NULL && strlen(next) > 0) {
        temp = realloc(out, sizeof(char*) * ((*size) + 1));

        if (temp == NULL) {
            fprintf(stderr, "Error allocating memory for string.\n");
            return NULL;
        }

        out = temp;
        out[(*size)++] = next;
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