#ifndef BUILTIN_H
#define BUILTIN_H

typedef struct Builtin
{
    char *Name;
    void (*Function)(char[10][100]);
} Builtin;

bool IsBuiltin(char argument[100]);
void RunBuiltin(char arguments[10][100]);
bool IsExecutable(char argument[100], char *filePath);

#endif
