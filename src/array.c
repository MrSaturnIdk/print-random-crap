/**
 * One helper for arrays
 * I don't wanna clog my main file
 */

#include "array.h"

#include <stddef.h>
#include <string.h>

int findIndexOfString(const char* array[], size_t len, const char* item) {
	size_t i = 0;

	for (i = 0; i < len; ++i) {
		if (!strcmp(array[i], item)) {
			return (int)i;
		}
	}
	return -1;
}
