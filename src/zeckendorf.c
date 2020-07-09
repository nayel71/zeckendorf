#include "../include/zeckendorf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const zint LIMIT = 9217463444206948444;
const zdigit ZERO = '0';
const zdigit ONE = '1';

bool zint_is_valid(const zint n) {
	return n > 0 && n <= LIMIT;
}

// iterates through z
// if successful, returns true, updates *len with the length of z, and, if print, prints z to stdout
// returns false if z is not a valid Zeckendorf representation
static bool iterate(const zrep z, int *len, bool print) {
	zrep it = z;
	*len = 0;
	if (!it || *it != ONE) {
		return false;
	}
	for (; *it; ++*len, ++it) {
		if (*it < ZERO || *it > ONE || *it - ZERO + *(it + 1) - ZERO > 1) {
			return false;
		} else if (print) {
			putchar(*it);
		}
	}
	if (print) {
		putchar('\n');
	}
	return true;
}

bool zrep_is_valid(const zrep z) {
	int len;
	return iterate(z, &len, false);
}

int z_length(const zrep z) {
	int len;
	if (iterate(z, &len, false)) {
		return len;
	} else {
		return 0;
	}
}

void z_print(const zrep z) {
	int len;
	iterate(z, &len, true);
}

zint strtozi(const char *str) {
	zint n = strtoll(str, NULL, 0);
	if (zint_is_valid(n)) {
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
