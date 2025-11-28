#include <stdio.h>
#include <string.h>

void REPLRead(char arguments[10][100]);
int REPLEval(char arguments[10][100]);
void REPLPrint(char arguments[10][100]);

int main(int argc, char *argv[])
{
    // Flush after every printf
    setbuf(stdout, NULL);

    while(true)
    {
        char arguments[10][100];

        REPLRead(arguments);

        if (REPLEval(arguments) > 0)
        {
            break;
        }

        REPLPrint(arguments);
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
        strncpy(arguments[x++], argument, 100);
        if (x >= 10)
        {
            break;
        }
        argument = strtok(NULL, " ");
    }
}

int REPLEval(char arguments[10][100])
{
    if (strcmp(arguments[0], "exit") == 0) 
    {
        return 1;
    }
    return 0;
}

void REPLPrint(char arguments[10][100])
{
    printf("%s: command not found\n", arguments[0]);
}
