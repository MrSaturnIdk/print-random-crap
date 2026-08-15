/**
 * Floods the terminal with characters
 * The code is self explanatory
 */

#include <cstdio>
#include <map>
#include <random>
#include <string>

int getRandomInt(int min, int max) {
    static std::random_device rd {};
    static std::mt19937 gen {rd()};

    std::uniform_int_distribution<> dist {min, max};
    return dist(gen);
}
char getRandomAsciiChar(bool noWhitespace) {
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
    std::map<std::string, int> correlatedNumbers {
        /// Printing modifiers
        {"--no-whitespace", 3},
        /// Misc
        {"--help", 1},
        {"--version", 2}
    };
    for (int i = 1; i < argc; i++) {
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
                std::printf("%s\n\n%s\n%s\n\n%s\n",
                    "Print Random Crap 1.2.0",
                    "Copyright © 2026 MrSaturnIdk.",
                    "Licensed under the AGPL-3.0-or-later.",
                    "Source code hosted at <https://github.com/MrSaturnIdk/print-random-crap>."
                );
                return 0;
            default:
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

    for (;;) {
        std::printf("%c", getRandomAsciiChar(noWhitespace));
        std::fflush(stdout);
    }
}
