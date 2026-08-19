/**
 * Helper functions for making random stuff (header)
 */

#ifndef HELPERS_RANDOM_HPP
#define HELPERS_RANDOM_HPP

#include <cstdint>

namespace helpers::random {

extern bool usingCustomSeed;
extern std::uint32_t randomSeed;
extern bool noWhitespace;
extern bool onlyWhitespace;

int getRandomInt(int min, int max);
char getRandomAsciiChar();

}

#endif
