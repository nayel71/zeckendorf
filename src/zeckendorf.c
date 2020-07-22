#include "../include/zeckendorf.h"
#include <stdlib.h>
#include <string.h>

const long long LIMIT = 9217463444206948444;
const char ZERO = '0';
const char ONE = '1';

zint *strtozi(const char *s) {
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

zrep *strtozr(const char *s) {
	if (rep_is_valid(s)) {
		zrep *ans = malloc(sizeof(zrep));
		ans->len = strlen(s);
		ans->val = malloc(ans->len * sizeof(char));
		memcpy(ans->val, s, ans->len * sizeof(char));
		return ans;
	} else {
		return NULL;
	}
}

char *zrtostr(const zrep *z) {
	char *s = malloc((z->len + 1) * sizeof(char));
	memcpy(s, z->val, z->len * sizeof(char));
	s[z->len] = '\0';
	return s;
}

void z_clear(zrep *z) {
	free(z->val);
	free(z);
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

	zrep *zans = malloc(sizeof(zrep));
	zans->val = ans;
	zans->len = pos;
	return zans;
}
