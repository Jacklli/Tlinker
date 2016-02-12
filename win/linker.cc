#include <stdio.h>
#include "tlinker.h"

typedef void (*PrintFuncPtr)(char * msg);
typedef void (* FuncPtr)(PrintFuncPtr pfunc, char * msg);

void printMsg(char * msg) {
    printf("%s", msg);
}

int main(int argCount, char ** args) {
    if (argCount != 2) {
        printf("linker /fullpath/test.obj\n");
	return -1;
    }
    char * objFile = args[1];
    char * entryFunctionName = "f1";
    struct Program * prg = linkFunction(entryFunctionName, objFile);
    FuncPtr func = (FuncPtr)prg->entry;
    func(printMsg, "my link ok\n");
    freeProgram(prg);
    return 1;
}
