/**
 * Floods the terminal with characters
 * The code is self explanatory
 */

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <random>
#include <string>
#include <unordered_map>

static bool usingCustomSeed {};
static bool noWhitespace {};
static std::uint32_t randomSeed {};

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

bool isCStringValidUnsignedInt(const char* string) {
    int i {};
    while (string[i] != '\0') {
        // Characters 0-9 use 48-57 in ASCII, so getting the static_casted to int version minus 48 will get you 0-9
        switch (static_cast<int> (string[i] - 48)) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            default:
                return false;
        }
        ++i;
    }
    return true;
}
std::uint32_t cStringToInt(const char* string) {
    int i {};
    std::uint32_t returnable {};
    while (string[i] != '\0') {
        int number {string[i] - 48};
        double placeValue {std::pow(10.0, i)};
        number *= placeValue;
        returnable += number;
        ++i;
    }
    return returnable;
}

int main(int argc, char* argv[]) {
    bool expectingSeed {};
    std::unordered_map<std::string, int> correlatedNumbers {
        /// Printing modifiers
        {"--no-whitespace", 3},
        {"--set-seed", 4},
        /// Misc
        {"--help", 1},
        {"--version", 2}
    };
    for (int i = 1; i < argc; ++i) {
        int num {correlatedNumbers[argv[i]]};
        switch (num) {
            /// Same order as in correlatedNumbers
            case 3:
                noWhitespace = true;
                break;
            case 4:
                expectingSeed = true;
                break;

            case 1:
                std::printf("%s%s%s\n%s\n%s\n\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
                    "Usage: ",
                    argv[0],
                    " [arguments]",
                    "Infinitely print random letters.",
                    "No arguments will print letters.",
                    "List of arguments:",
                    "Modifies printing",
                    "  --set-seed <seed>  Set random seed to <seed>.",
                    "  --no-whitespace    Does not print spaces, newlines or tabs.",
                    "Miscellaneous",
                    "  --help             Prints this screen.",
                    "  --version          Prints version."
                );
                return 0;
            case 2:
                std::printf("%s%s\n\n%s\n%s\n\n%s%s%s\n",
                    "Print Random Crap ",
                    PROJECT_VER,
                    "Copyright © 2026 MrSaturnIdk.",
                    "Licensed under the AGPL-3.0-or-later.",
                    "Source code hosted at <",
                    HOMEPAGE,
                    ">."
                );
                return 0;
            default:
                if (expectingSeed) {
                    std::uint32_t seed {};
                    std::string string {argv[i]};
                    if (!isCStringValidUnsignedInt(string.c_str())) {
                        std::string tempString {};
                        for (char c : string) {
                            tempString += c;
                        }
                        string = tempString;
                    }
                    seed = cStringToInt(string.c_str());
                    randomSeed = seed;
                    usingCustomSeed = true;
                    expectingSeed = false;
                    break;
                } else {
                    std::printf("%s%s%s\n%s%s%s\n",
                        "Unrecognized flag \"",
                        argv[i],
                        "\".",
                        "See \"",
                        argv[0],
                        " --help\" for details."
                    );
                    return -1;
                }
        }
    }

    for (;;) {
        std::printf("%c", getRandomAsciiChar());
        std::fflush(stdout);
    }
}
