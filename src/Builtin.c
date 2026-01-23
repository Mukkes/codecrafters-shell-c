#include "Builtin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void BuiltinExit(char[10][100]);
void BuiltinEcho(char[10][100]);
void BuiltinType(char[10][100]);

static Builtin Builtins[] = {{"exit", BuiltinExit}, {"echo", BuiltinEcho}, {"type", BuiltinType}};
int BuiltinsLength = sizeof(Builtins) / sizeof(Builtin);

void GetBuiltin(char argument[100], Builtin **builtin)
{
    for (int i = 0; i < BuiltinsLength; i++)
    {
        if (strcmp(argument, Builtins[i].Name) == 0)
        {
            *builtin = &Builtins[i];
            return;
        }
    }
}

bool IsBuiltin(char argument[100])
{
    Builtin *builtin = NULL;
    GetBuiltin(argument, &builtin);
    return builtin != NULL;
}

void RunBuiltin(char arguments[10][100])
{
    Builtin *builtin = NULL;
    GetBuiltin(arguments[0], &builtin);
    if (builtin != NULL)
    {
        builtin->Function(arguments);
    }
}

void BuiltinExit(char arguments[10][100])
{
    exit(0);
}

void BuiltinEcho(char arguments[10][100])
{
    for (int i = 1; i < 10; i++)
    {
        if (arguments[i][0] == '\0')
        {
            break;
        }
        printf("%s", arguments[i]);
        printf(" ");
    }
    printf("\n");
}

void BuiltinType(char arguments[10][100])
{
    if (IsBuiltin(arguments[1]))
    {
        printf("%s is a shell builtin", arguments[1]);
    }
    else
    {
        printf("%s: not found", arguments[1]);
    }
    printf("\n");
}
