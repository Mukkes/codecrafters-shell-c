#include "Builtin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void BuiltinExit(char[10][100]);
void BuiltinEcho(char[10][100]);
void BuiltinType(char[10][100]);
void BuiltinTest(char[10][100]);

static Builtin Builtins[] = {{"exit", BuiltinExit},
                             {"echo", BuiltinEcho},
                             {"type", BuiltinType},
                             {"test", BuiltinTest}};
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

bool IsExecutable(char argument[100], char *filePath)
{
    const char *pathValue = getenv("PATH");
    int pathLenght = strlen(pathValue);
    char copyPath[pathLenght + 1];
    strncpy(copyPath, pathValue, pathLenght + 1);
    char *path = strtok(copyPath, ":");
    while (path != NULL)
    {
        strcpy(filePath, path);
        strcat(filePath, "/");
        strcat(filePath, argument);
        struct stat buffer;
        if (stat(filePath, &buffer) == 0 && buffer.st_mode & S_IXUSR)
        {
            return true;
        }
        path = strtok(NULL, ":");
    }
    return false;
}

void BuiltinType(char arguments[10][100])
{
    char filePath[150];
    if (IsBuiltin(arguments[1]))
    {
        printf("%s is a shell builtin", arguments[1]);
    }
    else if (IsExecutable(arguments[1], filePath))
    {
        printf("%s is %s", arguments[1], filePath);
    }
    else
    {
        printf("%s: not found", arguments[1]);
    }
    printf("\n");
}

void BuiltinTest(char arguments[10][100])
{
    const char *pathValue = getenv("PATH");
    int pathLenght = strlen(pathValue);
    char copyPath[pathLenght + 1];
    strncpy(copyPath, pathValue, pathLenght + 1);
    char *path = strtok(copyPath, ":");
    while (path != NULL)
    {
        printf("%s\n", path);
        path = strtok(NULL, ":");
    }
    printf("\n");
}
