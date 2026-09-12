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

#include <stdint.h>
#include <stdio.h>

const char *programName = "";
/**
 * 1 = Bad input
 * 3 = Random seeding error
 */
int main(int argc, char *argv[]) {
    programName = argv[0];
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
                    "Usage: ", programName, " [arguments]\n"
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
                fprintf(stderr, "%s: %serror:%s %sunrecognized argument '%s'%s\n",
                    programName,
                    isatty(STDERR_FILENO) ? ANSI_BOLD ANSI_RED : "",
                    isatty(STDERR_FILENO) ? ANSI_RESET : "",
                    isatty(STDERR_FILENO) ? ANSI_BOLD : "",
                    argv[i],
                    isatty(STDERR_FILENO) ? ANSI_RESET : ""
                );
                fprintf(stderr, "%s: %snote:%s %ssee '%s --help' for details%s\n",
                    programName,
                    isatty(STDERR_FILENO) ? ANSI_BOLD ANSI_GRAY : "",
                    isatty(STDERR_FILENO) ? ANSI_RESET : "",
                    isatty(STDERR_FILENO) ? ANSI_BOLD : "",
                    programName,
                    isatty(STDERR_FILENO) ? ANSI_RESET : ""
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
