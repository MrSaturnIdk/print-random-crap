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

const char *PROGRAM_NAME = "";
int STDERR_TTY = 0;

/**
 * 1 = Bad input
 * 3 = Random seeding error
 */
int main(int argc, char *argv[]) {
    // Variables
    PROGRAM_NAME = argv[0];
    STDERR_TTY = isatty(STDERR_FILENO);
    const char *argumentLookupTable[] = {
        /// Printing modifiers
        "--no-whitespace",
        "--only-whitespace",
        /// Misc
        "--help",
        "--version",
    };

    // Read arguments
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
                    "Usage: ", PROGRAM_NAME, " [arguments]\n"
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
                    PROGRAM_NAME,
                    STDERR_TTY ? ANSI_BOLD ANSI_RED : "",
                    STDERR_TTY ? ANSI_RESET : "",
                    STDERR_TTY ? ANSI_BOLD : "",
                    argv[i],
                    STDERR_TTY ? ANSI_RESET : ""
                );
                fprintf(stderr, "%s: %snote:%s %ssee '%s --help' for details%s\n",
                    PROGRAM_NAME,
                    STDERR_TTY ? ANSI_BOLD ANSI_GRAY : "",
                    STDERR_TTY ? ANSI_RESET : "",
                    STDERR_TTY ? ANSI_BOLD : "",
                    PROGRAM_NAME,
                    STDERR_TTY ? ANSI_RESET : ""
                );
                return 1;
            }
        }
    }

    // Check seed fail
    if (getRandomAsciiChar() == '\0') {
        return 3;
    }

    // Actual loop
    for (;;) {
        printf("%c", getRandomAsciiChar());
        fflush(stdout);
    }
}
