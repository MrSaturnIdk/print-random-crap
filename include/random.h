/**
 * Helper functions for making random stuff (header)
 */

#ifndef RANDOM_H
#define RANDOM_H

#include <stdint.h>

extern int noWhitespace;
extern int onlyWhitespace;

int getRandomInt(int min, int max);
char getRandomAsciiChar(void);

#endif
