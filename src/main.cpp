/**
 * Floods the terminal with characters
 * The code is self explanatory
 */

#include <cstdio>
#include <random>

int getRandomInt(int min, int max) {
    static std::random_device rd {};
    static std::mt19937 gen {rd()};

    std::uniform_int_distribution<> dist {min, max};
    return dist(gen);
}
char getRandomAsciiChar() {
    int character {getRandomInt(30, 126)};
    switch (character) {
        case 30:
            return '\n';
        case 31:
            return '\t';
        default:
            return static_cast<char> (character);
    }
}

int main() {
    for (;;) {
        std::printf("%c", getRandomAsciiChar());
        std::fflush(stdout);
    }
}
