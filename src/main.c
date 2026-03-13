#include "Arguments.h"
#define _GNU_SOURCE
#include "Builtin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void ReadArguments(Arguments *arguments);

int main(int argc, char *argv[])
{
    // Flush after every printf
    setbuf(stdout, NULL);

    while (true)
    {
        Arguments *arguments;
        InitializeArguments(&arguments);

        ReadArguments(arguments);

        if (arguments->count == 0)
        {
            DeleteArguments(&arguments);
            continue;
        }

        char filePath[1150];
        if (IsBuiltin(arguments->values[0]))
        {
            RunBuiltin(arguments);
        }
        else if (IsExecutable(arguments->values[0], filePath))
        {
            pid_t pid = fork();
            if (pid == -1)
            {
                perror("fork");
                exit(EXIT_FAILURE);
            }
            else if (pid > 0)
            {
                int status;
                waitpid(pid, &status, 0);
            }
            else
            {
                if (execv(filePath, arguments->values))
                {
                    perror(filePath);
                    exit(127);
                }
                exit(0);
            }
        }
        else
        {
            printf("%s: command not found\n", arguments->values[0]);
        }
        DeleteArguments(&arguments);
    }

    return 0;
}

void ReadArguments(Arguments *arguments)
{
    char *input = NULL;
    size_t inputSize = 0;
    ssize_t numberRead;

    printf("$ ");
    numberRead = getline(&input, &inputSize, stdin);
    if (numberRead < 0)
    {
        free(input);
        exit(1);
    }

    size_t argumentSize = 2;
    size_t argumentIndex = 0;
    char *argument = malloc(sizeof(char) * argumentSize);
    bool isInsideSingleQuotes = false;
    for (int i = 0; i < numberRead; i++)
    {
        if (argumentIndex + 1 >= argumentSize)
        {
            argumentSize *= 2;
            char *newArgument = realloc(argument, sizeof(char) * argumentSize);
            if (newArgument == NULL)
            {
                // Should free input. Better error handling? Return error?
                exit(1);
            }
            argument = newArgument;
        }

        if (input[i] == ' ' && !isInsideSingleQuotes)
        {
            if (argumentIndex > 0)
            {
                AddArgument(arguments, argument);
                argumentIndex = 0;
                argument[argumentIndex + 1] = 0;
            }
        }
        else if (input[i] == '\n')
        {
            break;
        }
        else if (input[i] == '\'')
        {
            isInsideSingleQuotes = !isInsideSingleQuotes;
        }
        else
        {
            argument[argumentIndex] = input[i];
            argument[argumentIndex + 1] = 0;
            argumentIndex++;
        }
    }
    if (argumentIndex > 0)
    {
        AddArgument(arguments, argument);
    }
    free(argument);
    free(input);
}
