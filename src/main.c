#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Flush after every printf
    setbuf(stdout, NULL);

    // TODO: Uncomment the code below to pass the first stage
    printf("$ ");

    char input[100];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    printf("%s: command not found\n", input);

    return 0;
}
