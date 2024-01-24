/*
//	Travis Rau
//	G01169745
*/

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <stdbool.h>
#define maxSize 35

bool IsPrime(int);

int main(void) {
	int pipeline[2];
	int returnPipe[2];
	int currentNumber;
	int numberCounter;
	int returnNumber;
	int allNumbers[maxSize - 1];

	pipe(pipeline);
	pipe(returnPipe);

	for (int x = 2; x <= maxSize; x++) {
		allNumbers[x - 2] = x;
		write(pipeline[1], &allNumbers[x - 2], sizeof(int));
	}

	if (fork() == 0) {
		while (true) {
			read(returnPipe[0], (void*)&currentNumber, sizeof(int));
			if (currentNumber) {
				read(pipeline[0], (void*)&currentNumber, sizeof(int));
				if (IsPrime(currentNumber))
					currentNumber *= -1;
				write(returnPipe[1], &currentNumber, sizeof(int));
			}
			else {
                close(pipeline[0]);
                close(returnPipe[0]);
                exit(0);
            }
		}
	}
	else {
		numberCounter = 2;
		currentNumber = 1;
		while (numberCounter < maxSize - 1) {
			write(returnPipe[1], &currentNumber, sizeof(int));
			read(returnPipe[0], (void*)&returnNumber, sizeof(int));
			if (returnNumber < 0)
				printf("prime %d\n", returnNumber * -1);

			numberCounter++;
		}
        close(pipeline[1]);
        close(returnPipe[1]);
		returnNumber = 0;
		write(returnPipe[1], &returnNumber, sizeof(int));

		exit(0);
	}
	exit(0);
}

bool IsPrime(int number) {
	if (number <= 1)
		return false;
	if (number <= 3)
		return true;

	for(int x = 2; x < number; x++) {
		if (number % x == 0)
			return false;
	}

	return true;
}
