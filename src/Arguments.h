#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <stdio.h>

typedef struct Arguments
{
    int count;
    char **values;
} Arguments;

void InitializeArguments(Arguments **arguments);
void AddArgument(Arguments *arguments, char *value);
void DeleteArguments(Arguments **arguments);
void DeleteArgument(Arguments *arguments, size_t index);

#endif
