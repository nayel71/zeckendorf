#include <zeckendorf.h>
#include "zrep.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const long long LIMIT = 9217463444206948444;
const char ZERO = '0';
const char ONE = '1';

struct zint {
	long long val;
};

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

void *strtoz(ztype typ, const char *s) {
	switch (typ) {
	case INT: {
		char *end;
		long long n = strtoll(s, &end, 0);
		if (n > 0 && n <= LIMIT && !*end) {
			zint *ans = malloc(sizeof(zint));
			ans->val = n;
			return ans;
		} else {
			return NULL;
		}
	}
	case REP:
		if (rep_is_valid(s)) {
			size_t len = strlen(s);
			char *copy = malloc(len * sizeof(char));
			return zrep_new(memcpy(copy, s, len * sizeof(char)), len);
		} else {
			return NULL;
		}
	}
}

char *zrtostr(const zrep *z) {
	size_t len = zrep_len(z);
	char *s = malloc((len + 1) * sizeof(char));
	memcpy(s, zrep_arr(z), len * sizeof(char));
	s[len] = '\0';
	return s;
}

// maxfib(n, index, fib) computes the largest Fibonacci number <= n,
// stores it at fib and stores its index at ind
static void maxfib(const long long n, size_t *ind, long long *fib) {
	long long fib1 = 0;
	long long fib2 = 1;
	for (*ind = 1; fib1 + fib2 <= n; ++*ind) {
		*fib = fib1 + fib2;
		fib1 = fib2;
		fib2 = *fib;
	}
}

zrep *z_rep(const zint *n) {
	size_t ind1;
	long long fib;
	maxfib(n->val, &ind1, &fib);

	char *ans = malloc(ind1 * sizeof(char));
	size_t pos = 0;

	for (long long rem = n->val; rem > 0; maxfib(rem, &ind1, &fib)) {
		rem -= fib;
		size_t ind2;
		maxfib(rem, &ind2, &fib);
		ans[pos] = ONE;
		memset(ans + pos + 1, ZERO, (ind1 - ind2 - 1) * sizeof(char));
		pos += ind1 - ind2;
		
	} 

	return zrep_new(ans, pos);
}

void z_clear(ztype typ, void *ptr) {
	switch (typ) {
	case INT:
		free(ptr);
		break;
	case REP:
		zrep_free((zrep *)ptr);
	}
}

// message(typ) returns an error message based on typ
static const char *message(ztype typ) {
	switch (typ) {
	case INT:
		return "invalid argument";
	case REP:
		return "invalid Zeckendorf representation";
	}
}

int z_error(ztype typ, const char *param) {
	fprintf(stderr, "Zeckendorf Error: %s %s\n", message(typ), param);
	return EXIT_FAILURE;
}
