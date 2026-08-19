/**
 * Floods the terminal with characters
 * The code is self explanatory
 */

#include "helpers/conversion.hpp"
#include "helpers/random.hpp"

#include <cstdint>
#include <cstdio>
#include <string>
#include <unordered_map>

/// -1 = Bad input
int main(int argc, char* argv[]) {
    std::string expectedFlagParameter {};
    std::unordered_map<std::string, int> flagLookupTable {
        /// Printing modifiers
        {"--set-seed", 1},
        {"--no-whitespace", 2},
        {"--only-whitespace", 3},
        /// Misc
        {"--help", 4},
        {"--version", 5}
    };
    std::unordered_map<std::string, int> flagParameterLookupTable {
        {"randomSeed", 1}
    };
    for (int i {1}; i < argc; ++i) {
        int lookup {flagLookupTable[argv[i]]};
        switch (lookup) {
            /// Same order as in flagLookupTable
            case 1: {
                expectedFlagParameter = "randomSeed";
                break;
            }
            case 2: {
                if (helpers::random::onlyWhitespace) {
                    helpers::random::onlyWhitespace = false;
                }
                helpers::random::noWhitespace = true;
                break;
            }
            case 3: {
                if (helpers::random::noWhitespace) {
                    helpers::random::noWhitespace = false;
                }
                helpers::random::onlyWhitespace = true;
                break;
            }

            case 4: {
                std::printf("%s%s%s",
                    "Usage: ", argv[0], " [arguments]\n"
                    "Infinitely print random letters.\n"
                    "No arguments will print letters.\n\n"
                    "List of arguments:\n"
                    "Modifies printing\n"
                    "  --set-seed <seed>  Set random seed to <seed>.\n"
                    "  --no-whitespace    Does not print spaces, newlines or tabs.\n"
                    "  --only-whitespace  Only prints newlines.\n"
                    "Miscellaneous\n"
                    "  --help             Prints this screen.\n"
                    "  --version          Prints version.\n"
                );
                return 0;
            }
            case 5: {
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
                        if (!helpers::conversion::isStdStringValidUnsignedInt(string)) {
                            std::string tempString {};
                            for (char c : string) {
                                tempString += c;
                            }
                            string = tempString;
                        }
                        seed = helpers::conversion::stdStringToInt(string);
                        helpers::random::randomSeed = seed;
                        helpers::random::usingCustomSeed = true;
                        expectedFlagParameter = "";
                        break;
                    }
                    default: {
                        std::fprintf(stderr, "%s%s%s%s%s",
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

    if (expectedFlagParameter != "") {
        std::fprintf(stderr, "ERROR: Parameter for argument \"%s\" not given.\n", argv[argc - 1]);
        return -1;
    }

    for (;;) {
        std::printf("%c", helpers::random::getRandomAsciiChar());
        std::fflush(stdout);
    }
}
