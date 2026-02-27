#include "Arguments.h"
#include <stdlib.h>
#include <string.h>

void InitializeArguments(Arguments **arguments)
{
    void *argumentsPointer = malloc(sizeof(Arguments));
    if (argumentsPointer == NULL)
    {
        exit(1);
    }
    *arguments = argumentsPointer;
    (*arguments)->count = 0;
}

void AddArgument(Arguments *arguments, char *value)
{
    void *valuesPointer;
    if (arguments->count == 0)
    {
        valuesPointer = malloc(sizeof(char *));
    }
    else
    {
        valuesPointer =
            realloc(arguments->values, sizeof(char *) * (arguments->count + 1));
    }

    if (valuesPointer == NULL)
    {
        exit(1);
    }
    arguments->values = valuesPointer;

    int valueLenght = strlen(value);
    char *argumentPointer = malloc(sizeof(char) * (valueLenght + 1));
    arguments->values[arguments->count] = argumentPointer;
    strncpy(arguments->values[arguments->count], value, valueLenght);
    arguments->values[arguments->count][valueLenght] = '\0';
    arguments->count++;
}

void DeleteArguments(Arguments **arguments)
{
    for (int i = 0; i < (*arguments)->count; i++)
    {
        free((*arguments)->values[i]);
        (*arguments)->values[i] = NULL;
    }
    free((*arguments)->values);
    (*arguments)->values = NULL;
    free(*arguments);
    *arguments = NULL;
}
