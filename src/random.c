/**
 * Helper functions for making random stuff (source)
 */

#include "random.h"

#include "ansicolors.h"

#ifndef _WIN32
#   include <unistd.h>
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern const char *PROGRAM_NAME;
extern int STDERR_TTY;

/// Internal
/**
 * 0 = Success
 * 1 = Fail
 */
static int initSeed(void) {
#   ifndef _WIN32
    // Attempt /dev/urandom read first on Unix
    FILE *urandom = fopen("/dev/urandom", "r");
    unsigned seed = 0;
    size_t count = 0;
    if (urandom) {
        count = fread(&seed, 1, sizeof(seed), urandom);
        fclose(urandom);
    }
    if (count != 0) {
        srand(seed);
        return 0;
    }
#   endif
    time_t clock = time(NULL);
    if (clock == (time_t)-1) {
#       ifdef _WIN32
        fprintf(stderr, "%s: error: failed to get time\n", PROGRAM_NAME);
#       else
        fprintf(stderr,"%s: %serror:%s %sfailed to read /dev/urandom and get time%s\n",
            PROGRAM_NAME,
            STDERR_TTY ? ANSI_BOLD ANSI_RED : "",
            STDERR_TTY ? ANSI_RESET : "",
            STDERR_TTY ? ANSI_BOLD : "",
            STDERR_TTY ? ANSI_RESET : ""
        );
#       endif
        return 1;
    }
    srand((unsigned)clock);
    return 0;
}

/// For use
int noWhitespace = 0;
int onlyWhitespace = 0;
int getRandomInt(int min, int max) {
    static int needsInit = 1;
    if (needsInit) {
        int result = initSeed();
        if (result) {
            return -1;
        }
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
