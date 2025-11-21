#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Flush after every printf
    setbuf(stdout, NULL);

    while(true)
    {
        // TODO: Uncomment the code below to pass the first stage
        printf("$ ");

        char input[100];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        if (strcmp(input, "exit") == 0) 
        {
            break;
        }
        printf("%s: command not found\n", input);
    }

    return 0;
}
