#include "../include/zeckendorf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const zint LIMIT = 9217463444206948444;
const zdigit ZERO = '0';
const zdigit ONE = '1';

// checks if z is a valid Zeckendorf representation
static bool zrep_is_valid(const zrep z) {
	if (!z || *z != ONE) {
		return false;
	}
	for (zrep it = z; *it; ++it) {
		if (*it < ZERO || *it > ONE || *it - ZERO + *(it + 1) - ZERO > 1) {
			return false;
		}
	}
	return true;
}

int z_length(const zrep z) {
	return strlen(z);
}

void z_print(const zrep z) {
	puts(z);
}

zint strtozi(const char *str) {
	zint n = strtoll(str, NULL, 0);
	if (n > 0 && n <= LIMIT) {
		return n;
	} else {
		return 0;
	}
}

zrep strtozr(const char *str) {
	zrep z = strdup(str);
	if (zrep_is_valid(z)) {
		return z;
	} else {
		free(z);
		return NULL;
	}
}
