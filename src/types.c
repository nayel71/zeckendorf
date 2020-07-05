#include "../include/types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const z_int LIMIT = 9217463444206948444;
const z_digit ZERO = '0';
const z_digit ONE = '1';

bool z_int_is_valid(z_int n) {
	return n > 0 && n <= LIMIT;
}

bool z_rep_is_valid(const z_rep z) {
	if (z[0] != ONE) {
		return false;
	}
	for (int index = strlen(z) - 1; index > 0; index--) {
		if (z[index] < ZERO || z[index] > ONE || z[index] - ZERO + z[index-1] - ZERO > 1) {
			return false;
		}
	}
	return true;
}

z_int strtozi(const char *str) {
	z_int n = strtoll(str, NULL, 0);
	if (z_int_is_valid(n)) {
		return n;
	} else {
		exit(z_error(BOUND, str));
	}
}

z_rep strtozr(const char *str) {
	z_rep z = (z_rep)str;
	if (z_rep_is_valid(z)) {
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

void z_print(z_rep z) {
	puts(z);
}