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

int main(int argc, char* argv[]) {
    std::map<std::string, int> correlatedNumbers {
        /// Misc
        {"--help", 1},
        {"--version", 2}
    };
    for (int i = 1; i < argc; i++) {
        int num {correlatedNumbers[argv[i]]};
        switch (num) {
            case 1:
                std::printf("%s%s%s\n%s\n%s\n\n%s\n%s\n%s\n%s\n",
                    "Usage: ",
                    argv[0],
                    " [arguments]",
                    "Infinitely print random letters.",
                    "No arguments will print letters.",
                    "List of arguments:",
                    "Miscellaneous",
                    "  --help        Prints this screen.",
                    "  --version     Prints version."
                );
                return 0;
            case 2:
                std::printf("%s\n\n%s\n%s\n",
                    "Print Random Crap 1.0.0",
                    "Copyright © 2026 MrSaturnIdk",
                    "Licensed under the AGPL-3.0-or-later"
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
        std::printf("%c", getRandomAsciiChar());
        std::fflush(stdout);
    }
}
