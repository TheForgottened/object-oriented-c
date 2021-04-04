#ifndef UTILS_H
#define UTILS_H

#define BUFFER_SIZE 1024

// WARNING: this function ruins the original string.
char** splitString(char* str, char* delim, int* size);

// Turn every characters in a string to '\0'
char* resetString(char* str);

#endif /* UTILS_H */