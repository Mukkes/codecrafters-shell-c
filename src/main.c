#include <stdio.h>
#include <string.h>

void REPLRead(char *input, int sizeInput);
int REPLEval(char *input);
void REPLPrint(char *input);

int main(int argc, char *argv[])
{
    // Flush after every printf
    setbuf(stdout, NULL);

    while(true)
    {
        char input[1000];

        REPLRead(input, sizeof(input));

        if (REPLEval(input) > 0)
        {
            break;
        }

        REPLPrint(input);
    }

    return 0;
}

void REPLRead(char *input, int sizeInput)
{
    printf("$ ");
    fgets(input, sizeInput, stdin);
}

int REPLEval(char *input)
{
    input[strcspn(input, "\n")] = 0;
    if (strcmp(input, "exit") == 0) 
    {
        return 1;
    }
    return 0;
}

void REPLPrint(char *input)
{
    printf("%s: command not found\n", input);
}
