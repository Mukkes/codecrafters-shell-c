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
        valuesPointer = malloc(sizeof(char *) * 2);
    }
    else
    {
        valuesPointer =
            realloc(arguments->values, sizeof(char *) * (arguments->count + 2));
    }

    if (valuesPointer == NULL)
    {
        exit(1);
    }
    arguments->values = valuesPointer;

    int valueLenght = strlen(value);
    char *argumentPointer = malloc(sizeof(char) * (valueLenght + 1));
    if (argumentPointer == NULL)
    {
        exit(1);
    }
    arguments->values[arguments->count] = argumentPointer;

    strncpy(arguments->values[arguments->count], value, valueLenght);
    arguments->values[arguments->count][valueLenght] = '\0';
    arguments->values[arguments->count + 1] = NULL;
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

void DeleteArgument(Arguments *arguments, size_t index)
{
    if (index >= arguments->count)
    {
        exit(1);
    }

    free(arguments->values[index]);
    arguments->values[index] = NULL;

    for (size_t i = index; i < arguments->count; i++)
    {
        arguments->values[i] = arguments->values[i + 1];
    }

    arguments->values[arguments->count] = NULL;
    arguments->count--;
}
