/**
 * Floods the terminal with characters
 * The code is self explanatory
 */

#include <cstdio>
#include <random>
#include <string>
#include <unordered_map>

static bool noWhitespace {};

int getRandomInt(int min, int max) {
    static std::random_device rd {};
    static std::mt19937 gen {rd()};

    std::uniform_int_distribution<> dist {min, max};
    return dist(gen);
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

int main(int argc, char* argv[]) {
    bool noWhitespace {};
    std::unordered_map<std::string, int> correlatedNumbers {
        /// Printing modifiers
        {"--no-whitespace", 3},
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

            case 1:
                std::printf("%s%s%s\n%s\n%s\n\n%s\n%s\n%s\n%s\n%s\n%s\n",
                    "Usage: ",
                    argv[0],
                    " [arguments]",
                    "Infinitely print random letters.",
                    "No arguments will print letters.",
                    "List of arguments:",
                    "Modifies printing",
                    "  --no-whitespace  Does not print spaces, newlines or tabs.",
                    "Miscellaneous",
                    "  --help           Prints this screen.",
                    "  --version        Prints version."
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
                        int j {};
                        while (argv[i][j] != '\0') {
                            string += argv[i][j];
                            ++j;
                        }
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
