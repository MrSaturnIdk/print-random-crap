/** Helper functions for making random stuff (source) */

#include "random.h"

#ifndef _WIN32
#include <stddef.h>
#include <stdio.h>
#endif
#include <stdlib.h>
#include <time.h>

/**
 * 0 = Success
 * 1 = Fail
 */
static int initSeed(void) {
	time_t now = 0;
#	ifndef _WIN32
	/* Attempt /dev/urandom read first on Unix */
	FILE* urandom = NULL;
	size_t count = 0;
	unsigned seed = 0;

	urandom = fopen("/dev/urandom", "r");
	if (urandom) {
		count = fread(&seed, sizeof(seed), 1, urandom);
		fclose(urandom);
	}
	if (count) {
		srand(seed);
		return 0;
	}
#	endif
	now = time(NULL);
	if (now == (time_t)-1) {
		return 1;
	}
	srand((unsigned)now);
	return 0;
}

/** For use */
int getRandomInt(int min, int max) {
	static int needsInit = 1;
	int range = 0;
	int random = 0;

	if (needsInit) {
		int result = initSeed();
		if (result) {
			return -1;
		}
		needsInit = 0;
	}

	range = max - min + 1;
	random = rand() % range;
	return random + min;
}
char getRandomAsciiChar(int whitespace) {
	int character = 0;
	switch (whitespace) {
		case 1: {
			character = getRandomInt(33, 126);
			break;
		}
		case 2: {
			character = 30;
			break;
		}
		default: {
			character = getRandomInt(30, 126);
			break;
		}
	}

	switch (character) {
		case -1: {
			return '\0';
		}
		case 30: {
			return '\n';
		}
		case 31: {
			return '\t';
		}
		default: {
			return (char)character;
		}
	}
}
