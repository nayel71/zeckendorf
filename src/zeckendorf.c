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
	if (*it != ONE) {
		return false;
	}
	for (*len = 0; *it; ++*len, ++it) {
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
		exit(z_error(REP, z));
	}
}

void z_print(const zrep z) {
	int len;
	if (!iterate(z, &len, true)) {
		exit(z_error(REP, z));
	}
}

zint strtozi(const char *str) {
	zint n = strtoll(str, NULL, 0);
	if (zint_is_valid(n)) {
		return n;
	} else {
		exit(z_error(BOUND, str));
	}
}

zrep strtozr(const char *str) {
	zrep z = (zrep)str;
	if (zrep_is_valid(z)) {
		return z;
	} else {
		exit(z_error(REP, str));
	}
}

// returns an error message based on the error type
static const char *message(error_t err) {
	switch (err) {
		case BOUND: return "out-of-range argument";
		case REP:   return "invalid Zeckendorf representation";
	}
}

int z_error(error_t err, const char *param) {
	fprintf(stderr, "Error: %s %s\n", message(err), param);
	return EXIT_FAILURE;
}
