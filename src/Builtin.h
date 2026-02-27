#ifndef BUILTIN_H
#define BUILTIN_H

#include "Arguments.h"
typedef struct Builtin
{
    char *Name;
    void (*Function)(Arguments *arguments);
} Builtin;

bool IsBuiltin(char *argument);
void RunBuiltin(Arguments *arguments);
bool IsExecutable(char *argument, char *filePath);

#endif
