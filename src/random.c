/**
 * Helper functions for making random stuff (source)
 */

#ifdef _WIN32
#   include <time.h>
#else
#   include <stdio.h>
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

/// Internals
static uint32_t randomState = 0;
static void randomInit(void) {
#   ifdef _WIN32
    randomState = (uint32_t)time(NULL);
#   else
    FILE* urandom = fopen("/dev/urandom", "r");
    if (!urandom) {
        fprintf(stderr, "Failed to open /dev/urandom\n");
        exit(2); /// I/O fail
    }
    fread(&randomState, 1, sizeof(randomState), urandom);
    fclose(urandom);
#   endif
}
static void xorshift32(void) {
    randomState ^= randomState << 13;
    randomState ^= randomState >> 17;
    randomState ^= randomState << 5;
}

/// For use
int noWhitespace = 0;
int onlyWhitespace = 0;
int getRandomInt(int min, int max) {
    static int notInit = 1;
    if (notInit) {
        randomInit();
        notInit = 0;
    }
    xorshift32();
    uint32_t range = (uint32_t)(max - min + 1);
    return  min + (int)(randomState % range);
}
char getRandomAsciiChar(void) {
    int character = 0;
    if (noWhitespace) {
        character = getRandomInt(33, 126);
    } else if (onlyWhitespace) {
        character = 30;
    } else {
        character = getRandomInt(30, 126);
    }

    switch (character) {
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
