/*
//	Travis Rau
//	G01169745
*/

#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
    char *nargs[MAXARG];
    int argCount = 0;
    for(int i = 1; i < argc; i++)
        nargs[argCount++] = argv[i];

    char tempChar = 0;
    char buffer[1024];

    int status = 1;
    while(status) {
        int position = 0;
        int argumentStartPosition = 0;

        while(1) {
            status = read(0, &tempChar, 1);
            if(status == 0) exit(0);
            if(tempChar != ' ' && tempChar != '\n') {
                buffer[position++] = tempChar;
            } else if(tempChar == ' ') {
                buffer[position++] = 0;
                nargs[argCount++] = &buffer[argumentStartPosition];
                argumentStartPosition = position;
            } else if(tempChar == '\n') {
                nargs[argCount++] = &buffer[argumentStartPosition];
                argumentStartPosition = position;
                break;
            }
        }

        if(fork() == 0) {
            exec(nargs[0], nargs);
        } else {
            wait(0);
        }
    }
    exit(0);
}