/*
//	Travis Rau
//	G01169745
*/

#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
    int parent_pipe[2], child_pipe[2];
    char buffer[10];

    if(pipe(parent_pipe) < 0 || pipe(child_pipe) < 0) {
        fprintf(2, "Error: Can't create pipe!\n");
        exit(1);
    }
    if(fork() == 0) {  //children process
        close(parent_pipe[1]); //close write
        close(child_pipe[0]);
        read(parent_pipe[0], buffer, 1);
        if(buffer[0] == 'i') {
            printf("%d: received ping\n", getpid());
        }
        write(child_pipe[1], "o", 1);
        close(parent_pipe[0]);
        close(child_pipe[1]);
    } else {
        close(parent_pipe[0]);
        close(child_pipe[1]);
        write(parent_pipe[1], "i", 1);
        read(child_pipe[0], buffer, 1);
        if(buffer[0] == 'o') {
            printf("%d: received pong\n", getpid());
        }
        close(parent_pipe[1]);
        close(child_pipe[0]);
    }
    exit(0);

}