#include "Builtin.h"
#include <stdio.h>
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

        if (IsBuiltin(arguments[0]))
        {
            RunBuiltin(arguments);
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
