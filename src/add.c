#include "../include/zeckendorf.h"
#include "../include/arithmetic.h"
#include "add.h"
#include <stdlib.h>
#include <string.h>

// cf. paper by Frougny et al.

// add_same_len(s1, s2, len, rlen) returns a char array representing the sum of Zeckendorf representations
// given by s1 and s2, and stores its length at rlen
// requires: s1 and s2 represent Zeckendorf representations of length len with possible leading ZEROs, rlen != NULL
// effects: allocates memory (caller must free), updates *rlen
static char *add_same_len(const char *s1, const char *s2, size_t len, size_t *rlen) {
	const char TWO = ONE + 1;
	const char THREE = TWO + 1;

	if (s1[0] == ONE && s2[0] == ONE) {
		char *cpy1 = malloc((len + 1) * sizeof(char));
		memcpy(cpy1 + 1, s1, len * sizeof(char));
		cpy1[0] = ZERO;

		char *cpy2 = malloc((len + 1) * sizeof(char));
		memcpy(cpy2 + 1, s2, len * sizeof(char));
		cpy2[0] = ZERO;

		char *ans = add_same_len(cpy1, cpy2, len, rlen);
		free(cpy1);
		free(cpy2);
		return ans;
	}
	
	char *ans = malloc((len + 1) * sizeof(char)); 
	ans[0] = ZERO; 
	
	// add pointwise
	for (int i = 1; i <= len; i++) {
		if (s1[i - 1] != s2[i - 1]) {
			ans[i] = ONE;
		} else if (s1[i - 1] == s2[i - 1] && s1[i - 1] == ONE) {
			ans[i] = TWO;
		} else {
			ans[i] = ZERO;
		}
	}

	// first stage

	// eliminate TWOs
	for (int i = 0; i <= len - 2; i++) {
		if (i < len - 2 && ans[i] == ZERO && ans[i + 1] == TWO && ans[i + 2] == ZERO) {
			ans[i] = ONE;
			ans[i + 1] = ZERO;
			ans[i + 2] = ZERO;
			ans[i + 3] += 1;
		} else if (i < len - 2 && ans[i] == ZERO && ans[i + 1] == THREE && ans[i + 2] == ZERO) {
			ans[i] = ONE;
			ans[i + 1] = ONE;
			ans[i + 2] = ZERO;
			ans[i + 3] += 1;
		} else if (ans[i] == ZERO && ans[i + 1] == TWO && ans[i + 2] == ONE) {
			ans[i] = ONE;
			ans[i + 1] = ONE;
			ans[i + 2] = ZERO;
		} else if (ans[i] == ZERO && ans[i + 1] == ONE && ans[i + 2] == TWO) {
			ans[i] = ONE;
			ans[i + 1] = ZERO;
			ans[i + 2] = ONE;
		} 
	}

	// clean-up
	if (len > 1 && ans[len - 2] == ZERO && ans[len - 1] == THREE && ans[len] == ZERO) {
		ans[len - 2] = ONE;
		ans[len - 1] = ONE;
		ans[len] = ONE;
	} else if (len > 1 && ans[len - 2] == ZERO && ans[len - 1] == TWO && ans[len] == ZERO) {
		ans[len - 2] = ONE;
		ans[len - 1] = ZERO;
		ans[len] = ONE;
	} else if (len > 2 && ans[len - 3] == ZERO && ans[len - 2] == ONE && ans[len - 1] == TWO && ans[len] == ZERO) {
		ans[len - 3] = ONE;
		ans[len - 2] = ZERO;
		ans[len - 1] = ONE;
		ans[len] = ZERO;
	} else if (ans[len - 1] == ZERO && ans[len] == THREE) {
		ans[len - 1] = ONE;
		ans[len] = ONE;
	} else if (ans[len - 1] == ZERO && ans[len] == TWO) {
		ans[len - 1] = ONE;
		ans[len] = ZERO;
	}

	// second stage
	
	// first pass from right to left
	for (int i = len; i >= 2; i--) {
		if (ans[i] == ONE && ans[i - 1] == ONE && ans[i - 2] == ZERO) {
			ans[i] = ZERO;
			ans[i - 1] = ZERO;
			ans[i - 2] = ONE;
		}
	}

	// second pass from left to right
	for (int i = 0; i <= len - 2; i++) {
		if (ans[i] == ZERO && ans[i + 1] == ONE && ans[i + 2] == ONE) {
			ans[i] = ONE;
			ans[i + 1] = ZERO;
			ans[i + 2] = ZERO;
		}
	}

	// remove leading ZEROs
	char *pos = memchr(ans, ONE, len * sizeof(char));
	*rlen = len + 1 + ans - pos;
	memmove(ans, pos, *rlen * sizeof(char));

	return ans;
}

char *add_len(const char *s1, const char *s2, size_t len1, size_t len2, size_t *rlen) {
	// add leading ZEROs to make lengths equal, then use add_same_len
	if (len1 > len2) {
		char *cp = malloc(len1 * sizeof(char));
		memset(cp, ZERO, (len1 - len2) * sizeof(char));
		memcpy(cp + len1 - len2, s2, len2 * sizeof(char));
		char *ans = add_same_len(s1, cp, len1, rlen);
		free(cp);
		return ans;
	} else if (len1 < len2) {
		return add_len(s2, s1, len2, len1, rlen);
	} else {
		return add_same_len(s1, s2, len1, rlen);
	}
}

zrep *z_add(const zrep *z1, const zrep *z2) {
	zrep *zans = malloc(sizeof(zrep));
	zans->val = add_len(z1->val, z2->val, z1->len, z2->len, &zans->len);
	return zans;
}
