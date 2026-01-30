#include "Builtin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ReadArguments(char arguments[10][100]);

int main(int argc, char *argv[])
{
    // Flush after every printf
    setbuf(stdout, NULL);

    while (true)
    {
        char arguments[10][100];
        char output[1000];
        memset(output, '\0', sizeof(output));

        ReadArguments(arguments);

        char filePath[1150];
        if (IsBuiltin(arguments[0]))
        {
            RunBuiltin(arguments);
        }
        else if (IsExecutable(arguments[0], filePath))
        {
            for (int i = 1; i < 10; i++)
            {
                if (arguments[i][0] == '\0')
                {
                    break;
                }
                strcat(filePath, " ");
                strcat(filePath, arguments[i]);
            }
            system(filePath);
        }
        else
        {
            printf("%s: command not found\n", arguments[0]);
        }
    }

    return 0;
}

void ReadArguments(char arguments[10][100])
{
    char input[1000];
    char *argument;
    int x = 0;

    printf("$ ");
    fgets(input, sizeof(input), stdin);

    argument = strtok(input, " ");
    while (argument != NULL)
    {
        argument[strcspn(argument, "\n")] = 0;
        strncpy(arguments[x++], argument, sizeof(input));
        if (x >= 10)
        {
            break;
        }
        argument = strtok(NULL, " ");
    }
}
