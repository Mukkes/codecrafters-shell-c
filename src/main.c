#include <stdio.h>
#include <string.h>

void REPLRead(char arguments[10][100]);
int REPLEval(char arguments[10][100], char output[1000]);
void REPLPrint(char output[1000]);

int main(int argc, char *argv[])
{
    // Flush after every printf
    setbuf(stdout, NULL);

    while (true)
    {
        char arguments[10][100];
        char output[1000];
        memset(output, '\0', sizeof(output));

        REPLRead(arguments);

        if (REPLEval(arguments, output) > 0)
        {
            break;
        }

        REPLPrint(output);
    }

    return 0;
}

void REPLRead(char arguments[10][100])
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

int REPLEval(char arguments[10][100], char output[1000])
{
    if (strcmp(arguments[0], "exit") == 0)
    {
        return 1;
    }
    else if (strcmp(arguments[0], "echo") == 0)
    {
        for (int i = 1; i < 10; i++)
        {
            if (arguments[i][0] == '\0')
            {
                break;
            }
            strcat(output, arguments[i]);
            strcat(output, " ");
        }
    }
    else if (strcmp(arguments[0], "type") == 0)
    {
        if ((strcmp(arguments[1], "echo") == 0) || (strcmp(arguments[1], "exit") == 0) ||
            (strcmp(arguments[1], "type") == 0))
        {
            snprintf(output, 1000, "%s is a shell builtin", arguments[1]);
        }
        else
        {
            snprintf(output, 1000, "%s: not found", arguments[1]);
        }
    }
    else
    {
        snprintf(output, 1000, "%s: command not found", arguments[0]);
    }
    return 0;
}

void REPLPrint(char output[1000])
{
    printf("%s\n", output);
}
