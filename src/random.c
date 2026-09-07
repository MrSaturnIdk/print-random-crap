/**
 * Helper functions for making random stuff (source)
 */

#include "ansicolors.h"

#ifndef _WIN32
#   include <unistd.h>
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/// Internal
static void initSeed(void) {
#   ifndef _WIN32
    // Attempt /dev/urandom read first on Unix
    FILE *urandom = fopen("/dev/urandom", "r");
    if (urandom) {
        unsigned seed = 0;
        fread(&seed, 1, sizeof(seed), urandom);
        fclose(urandom);
        srand(seed);
        return;
    }
#   endif
    time_t clock = time(NULL);
    if (clock == (time_t)-1) {
#       ifdef _WIN32
        fprintf(stderr, "Error: Failed to get time\n");
#       else
        fprintf(stderr, isatty(STDERR_FILENO)
            ? ANSI_BOLD ANSI_RED "Error:" ANSI_RESET " Failed to read /dev/urandom and get time\n"
            : "Error: Failed to read /dev/urandom and get time\n"
        );
#       endif
        exit(3);
    }
    srand((unsigned)clock);
}

/// For use
int noWhitespace = 0;
int onlyWhitespace = 0;
int getRandomInt(int min, int max) {
    static int needsInit = 1;
    if (needsInit) {
        initSeed();
        needsInit = 0;
    }
    return rand() % (max - min + 1) + min;
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
