/**
 * One helper for arrays
 * I don't wanna clog my main file
 */

#include "arrayhelp.h"

#include <stddef.h>
#include <string.h>

int findIndexOfStringFromNullArray(const char *array[], const char *item) {
    for (int i = 0; array[i]; ++i) {
        if (!strcmp(array[i], item)) {
            return i;
        }
    }
    return -1;
}
