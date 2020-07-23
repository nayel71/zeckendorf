#include "../include/zeckendorf.h"
#include "../include/arithmetic.h"
#include <stdlib.h>
#include <string.h>

// easy_mul(len1, len2, rlen) returns the product of Zeckendorf representations of lengths len1 and len2
// each containing a single ONE
// effects: allocates memory (caller must call z_clear)
static zrep *easy_mul(const size_t len1, const size_t len2) {
	if (len2 < len1) {
		return easy_mul(len2, len1);
	}

	zrep *zans = malloc(sizeof(zrep));
	zans->len = len1 + len2 - 1;
	char *ans = malloc(zans->len * sizeof(char));

	const size_t ind1 = len1 + 1;
	const size_t ind2 = len2 + 1;
	const size_t rem = ind1 % 2;

	for (size_t j = 0; j < 2 * ind1 - 4 - 2 * rem; ++j) {
		if (j % 4 == 0) {
			ans[j] = ONE;
		} else {
			ans[j] = ZERO;
		}
	}

	if (rem == 0) {
		ans[2 * ind1 - 4] = ONE;
	} else if (ind2 == ind1) {
		ans[2 * ind1 - 6] = ONE;
		ans[2 * ind1 - 5] = ZERO;
		ans[2 * ind1 - 4] = ONE;
	} else {
		ans[2 * ind1 - 6] = ONE;
		ans[2 * ind1 - 5] = ZERO;
		ans[2 * ind1 - 4] = ZERO;
		ans[2 * ind1 - 3] = ONE;
	}

	for (size_t j = rem + 1; j <= ind2 - ind1; ++j) {
		ans[2 * ind1 - 4 + j] = ZERO;
	}

	zans->val = ans;
	return zans;
}

zrep *z_mul(const zrep *z1, const zrep *z2) {
	// split z1 and z2 into sums of Fibonacci numbers, then multiply everything out
	char *s1 = z1->val;
	char *s2 = z2->val;
	size_t len1 = z1->len;
	size_t len2 = z2->len;
	size_t num1 = 0; // number of ONEs in z1
	size_t num2 = 0; // number of ONEs in z2

	for (size_t i = 0; i < len1; ++i) {
		if (s1[i] == ONE) {
			++num1;
		}
	}

	for (size_t i = 0; i < len2; ++i) {
		if (s2[i] == ONE) {
			++num2;
		}
	}

	size_t *lens1 = malloc(num1 * sizeof(size_t));
	size_t *lens2 = malloc(num2 * sizeof(size_t));

	for (size_t i = 0, j = 0; i < len1; ++i) {
		if (s1[i] == ONE) {
			lens1[j] = len1 - i;
			++j;
		}
	}

	for (size_t i = 0, j = 0; i < len2; ++i) {
		if (s2[i] == ONE) {
			lens2[j] = len2 - i;
			++j;
		}
	}

	zrep *sum;

	for (size_t k = num2; k > 0; --k) {
		for (size_t j = num1; j > 0; --j) {
			zrep *summand = easy_mul(lens1[j - 1], lens2[k - 1]);
			if (k == num2 && j == num1) {
				sum = summand;
			} else {
				zrep *temp = sum;
				sum = z_add(sum, summand);
				z_clear(temp);
				z_clear(summand);
			}
		}
	}

	// clean-up
	free(lens1);
	free(lens2);

	return sum;
}
