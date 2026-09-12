/**
 * Floods the terminal with characters
 * The code is self explanatory
 */

#include "ansicolors.h"
#include "array.h"
#include "random.h"

// I am not dealing with Windows quirks for ANSI color codes
#ifdef _WIN32
#   define isatty(x) 0
#else
#   include <unistd.h>
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/**
 * 1 = Bad input
 * 2 = I/O fail
 * 3 = Clock fail
 */
int main(int argc, char *argv[]) {
    const char *argumentLookupTable[] = {
        /// Printing modifiers
        "--no-whitespace",
        "--only-whitespace",
        /// Misc
        "--help",
        "--version",
    };
    for (int i = 1; i < argc; ++i) {
        int lookup = findIndexOfString(
            argumentLookupTable,
            sizeof(argumentLookupTable) / sizeof(argumentLookupTable[0]),
            argv[i]
        );
        switch (lookup) {
            /// Same order as in argumentLookupTable
            case 0: {
                if (onlyWhitespace) {
                    onlyWhitespace = 0;
                }
                noWhitespace = 1;
                break;
            }
            case 1: {
                if (noWhitespace) {
                    noWhitespace = 0;
                }
                onlyWhitespace = 1;
                break;
            }

            case 2: {
                printf("%s%s%s",
                    "Usage: ", argv[0], " [arguments]\n"
                    "Infinitely print random letters.\n"
                    "No arguments will print letters.\n\n"
                    "List of arguments:\n"
                    "Modifies printing\n"
                    "  --no-whitespace    Does not print spaces, newlines or tabs.\n"
                    "  --only-whitespace  Only prints newlines.\n"
                    "Miscellaneous\n"
                    "  --help             Prints this screen.\n"
                    "  --version          Prints version.\n"
                );
                return 0;
            }
            case 3: {
                printf("%s",
                    "Print Random Crap " PROJECT_VER "\n\n"
                    "Copyright © 2026 MrSaturnIdk.\n"
                    "Licensed under the AGPL-3.0-or-later.\n\n"
                    "Source code hosted at <" HOMEPAGE ">.\n"
                );
                return 0;
            }
            default: {
                fprintf(stderr, "%s%s%s%s%s",
                    isatty(STDERR_FILENO)
                        ? ANSI_BOLD ANSI_RED "Error:" ANSI_RESET " Unrecognized flag \""
                        : "Error: Unrecognized flag \"",
                    argv[i], "\".\n"
                    "See \"", argv[0], " --help\" for details.\n"
                );
                return 1;
            }
        }
    }

    for (;;) {
        printf("%c", getRandomAsciiChar());
        fflush(stdout);
    }
}
