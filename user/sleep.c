/*
//	Travis Rau
//	G01169745
*/

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Usage: $sleep NUMBER_OF_TICKS\n");
		exit(1);
	}

	unsigned int ticks = atoi(argv[1]);
	sleep(ticks);

	exit(0);
}
