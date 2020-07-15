#include "../include/zeckendorf.h"
#include <stdlib.h>
#include <string.h>

const zint LIMIT = 9217463444206948444;
const char ZERO = '0';
const char ONE = '1';

zint strtozi(const char *str) {
	char *endptr;
	zint n = strtoll(str, &endptr, 0);
	if (n > 0 && n <= LIMIT && !*endptr) {
		return n;
	} else {
		return 0;
	}
}

// checks if s represents a valid Zeckendorf representation
static bool rep_is_valid(const char *s) {
	if (!s || *s != ONE) {
		return false;
	}
	for (const char *it = s + 1; *it; ++it) {
		if (*it < ZERO || *it > ONE || *it - ZERO + *(it - 1) - ZERO > 1) {
			return false;
		}
	}
	return true;
}

zrep strtozr(const char *s) {
	if (rep_is_valid(s)) {
		return strdup(s);
	} else {
		return NULL;
	}
}

char *zrtostr(const zrep z) {
	return strdup(z);
}

int z_length(const zrep z) {
	return strlen(z);
}

void z_copy(const zrep z1, zrep *z2) {
	int len = z_length(z1);
	*z2 = realloc(*z2, (len + 1) * sizeof(char));
	memcpy(*z2, z1, (len + 1) * sizeof(char));
}

void z_clear(zrep *z) {
	free(*z);
}

// maxfib(n, index, fib) computes the largest Fibonacci number <= n,
// stores it at fib and stores its index at index
static void maxfib(const zint n, int *index, zint *fib) {
	zint fib1 = 0;
	zint fib2 = 1;
	for (*index = 1; fib1 + fib2 <= n; ++*index) {
		*fib = fib1 + fib2;
		fib1 = fib2;
		fib2 = *fib;
	}
}

zrep z_rep(const zint n) {
	int index;
	zint fib;
	maxfib(n, &index, &fib);

	char *ans = malloc(index * sizeof(char));
	int i = 0;

	for (zint rem = n; rem > 0; maxfib(rem, &index, &fib)) {
		rem -= fib;
		int next_index;
		maxfib(rem, &next_index, &fib);
		ans[i] = ONE;
		memset(ans + i + 1, ZERO, (index - next_index - 1) * sizeof(char));
		i += index - next_index;
		
	} 

	ans[i] = '\0'; // at this point, i == original index - 1 

	zrep zans = strtozr(ans);
	free(ans);
	return zans;
}
