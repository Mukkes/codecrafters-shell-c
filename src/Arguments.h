#ifndef ARGUMENTS_H
#define ARGUMENTS_H

typedef struct Arguments
{
    int count;
    char **values;
} Arguments;

void InitializeArguments(Arguments **arguments);
void AddArgument(Arguments *arguments, char *value);
void DeleteArguments(Arguments **arguments);

#endif
