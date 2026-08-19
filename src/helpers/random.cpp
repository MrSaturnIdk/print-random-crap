/**
 * Helper functions for making random stuff (source)
 */

#include "helpers/random.hpp"

#include <cstdint>
#include <random>

namespace helpers::random {

bool usingCustomSeed {};
std::uint32_t randomSeed {};
bool noWhitespace {};
bool onlyWhitespace {};

int getRandomInt(int min, int max) {
    if (usingCustomSeed) {
        static std::mt19937 gen {randomSeed};

        std::uniform_int_distribution<> dist {min, max};
        return dist(gen);
    } else {
        static std::random_device rd {};
        static std::mt19937 gen {rd()};

        std::uniform_int_distribution<> dist {min, max};
        return dist(gen);
    }
}
char getRandomAsciiChar() {
    int character {};
    if (noWhitespace) {
        character = getRandomInt(33, 126);
    } else if (onlyWhitespace) {
        character = 30;
    } else {
        character = getRandomInt(30, 126);
    }

    switch (character) {
        case 30:
            return '\n';
        case 31:
            return '\t';
        default:
            return static_cast<char> (character);
    }
}

}
