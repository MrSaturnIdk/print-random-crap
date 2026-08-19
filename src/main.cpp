/**
 * Floods the terminal with characters
 * The code is self explanatory
 */

#include <cmath>
#include <cstddef>
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

bool isStdStringValidUnsignedInt(std::string string) {
    for (char c : string) {
        // Characters 0-9 use 48-57 in ASCII, so getting the static_casted to int version minus 48 will get you 0-9
        switch (static_cast<int> (c - 48)) {
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
    }
    return true;
}
std::uint32_t stdStringToInt(std::string string) {
    std::uint32_t returnable {};
    for (std::size_t i {}; i < string.length(); ++i) {
        int number {string[i] - 48};
        double placeValue {std::pow(10.0, i)};
        number *= placeValue;
        returnable += number;
    }
    return returnable;
}

int main(int argc, char* argv[]) {
    std::string expectedFlagParameter {};
    std::unordered_map<std::string, int> flagLookupTable {
        /// Printing modifiers
        {"--no-whitespace", 3},
        {"--set-seed", 4},
        /// Misc
        {"--help", 1},
        {"--version", 2}
    };
    std::unordered_map<std::string, int> flagParameterLookupTable {
        {"randomSeed", 1}
    };
    for (int i {1}; i < argc; ++i) {
        int lookup {flagLookupTable[argv[i]]};
        switch (lookup) {
            /// Same order as in flagLookupTable
            case 3: {
                noWhitespace = true;
                break;
            }
            case 4: {
                expectedFlagParameter = "randomSeed";
                break;
            }

            case 1: {
                std::printf("%s%s%s",
                    "Usage: ", argv[0], " [arguments]\n"
                    "Infinitely print random letters.\n"
                    "No arguments will print letters.\n\n"
                    "List of arguments:\n"
                    "Modifies printing\n"
                    "  --set-seed <seed>  Set random seed to <seed>.\n"
                    "  --no-whitespace    Does not print spaces, newlines or tabs.\n"
                    "Miscellaneous\n"
                    "  --help             Prints this screen.\n"
                    "  --version          Prints version.\n"
                );
                return 0;
            }
            case 2: {
                std::printf("%s",
                    "Print Random Crap " PROJECT_VER "\n\n"
                    "Copyright © 2026 MrSaturnIdk.\n"
                    "Licensed under the AGPL-3.0-or-later.\n\n"
                    "Source code hosted at <" HOMEPAGE ">.\n"
                );
                return 0;
            }
            default: {
                int lookup {flagParameterLookupTable[expectedFlagParameter]};
                switch (lookup) {
                    /// In the same order as flagParameterLookupTable, similar to flagLookupTable
                    case 1: {
                        std::uint32_t seed {};
                        std::string string {argv[i]};
                        if (!isStdStringValidUnsignedInt(string)) {
                            std::string tempString {};
                            for (char c : string) {
                                tempString += c;
                            }
                            string = tempString;
                        }
                        seed = stdStringToInt(string);
                        randomSeed = seed;
                        usingCustomSeed = true;
                        expectedFlagParameter = "";
                        break;
                    }
                    default: {
                        std::printf("%s%s%s%s%s",
                            "ERROR: Unrecognized flag \"", argv[i], "\".\n"
                            "See \"", argv[0], " --help\" for details.\n"
                        );
                        return -1;
                    }
                }
                break;
            }
        }
    }

    for (;;) {
        std::printf("%c", getRandomAsciiChar());
        std::fflush(stdout);
    }
}
