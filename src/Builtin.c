#include "Builtin.h"
#include "Arguments.h"
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void BuiltinExit(Arguments *arguments);
void BuiltinEcho(Arguments *arguments);
void BuiltinType(Arguments *arguments);
void BuiltinPwd(Arguments *arguments);
void BuiltinTest(Arguments *arguments);

static Builtin Builtins[] = {{"exit", BuiltinExit},
                             {"echo", BuiltinEcho},
                             {"type", BuiltinType},
                             {"pwd", BuiltinPwd},
                             {"test", BuiltinTest}};
int BuiltinsLength = sizeof(Builtins) / sizeof(Builtin);

void GetBuiltin(char *argument, Builtin **builtin)
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

bool IsBuiltin(char *argument)
{
    Builtin *builtin = NULL;
    GetBuiltin(argument, &builtin);
    return builtin != NULL;
}

void RunBuiltin(Arguments *arguments)
{
    Builtin *builtin = NULL;
    GetBuiltin(arguments->values[0], &builtin);
    if (builtin != NULL)
    {
        builtin->Function(arguments);
    }
}

void BuiltinExit(Arguments *arguments)
{
    exit(0);
}

void BuiltinEcho(Arguments *arguments)
{
    for (int i = 1; i < arguments->count; i++)
    {
        printf("%s", arguments->values[i]);
        printf(" ");
    }
    printf("\n");
}

bool IsExecutable(char *argument, char *filePath)
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

void BuiltinType(Arguments *arguments)
{
    char filePath[150];
    if (IsBuiltin(arguments->values[1]))
    {
        printf("%s is a shell builtin", arguments->values[1]);
    }
    else if (IsExecutable(arguments->values[1], filePath))
    {
        printf("%s is %s", arguments->values[1], filePath);
    }
    else
    {
        printf("%s: not found", arguments->values[1]);
    }
    printf("\n");
}

void BuiltinPwd(Arguments *arguments)
{
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
    }
    else
    {
        exit(1);
    }
}

void BuiltinTest(Arguments *arguments)
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
