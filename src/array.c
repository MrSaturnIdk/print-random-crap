/**
 * One helper for arrays
 * I don't wanna clog my main file
 */

#include "array.h"

#include <stddef.h>
#include <string.h>

int findIndexOfStringFromNullArray(const char *restrict array[], const char *restrict item) {
    for (size_t i = 0; array[i]; ++i) {
        if (!strcmp(array[i], item)) {
            return (int)i;
        }
    }
    return -1;
}
