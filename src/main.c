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
        char *executableArguments[11];
        if (IsBuiltin(arguments->values[0]))
        {
            RunBuiltin(arguments);
        }
        else if (IsExecutable(arguments->values[0], filePath))
        {
            executableArguments[0] = arguments->values[0];
            int i;
            for (i = 1; i < arguments->count; i++)
            {
                executableArguments[i] = arguments->values[i];
            }
            executableArguments[i] = NULL;
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
                if (execv(filePath, executableArguments))
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
    char input[1000];
    char *argument;

    printf("$ ");
    fgets(input, sizeof(input), stdin);

    argument = strtok(input, " ");
    while (argument != NULL && strlen(argument) > 0 && argument[0] != '\n')
    {
        argument[strcspn(argument, "\n")] = 0;
        AddArgument(arguments, argument);
        argument = strtok(NULL, " ");
    }
}
