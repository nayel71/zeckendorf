#include "../include/zeckendorf.h"
#include "../include/arithmetic.h"
#include "add.h"
#include <stdlib.h>
#include <string.h>

// easy_mul(len1, len2, rlen) returns a char array representing the product of Zeckendorf representations
// of lengths len1 and len2 each containing a single ONE, and stores its length at rlen
// requires: rlen != NULL
// effects: allocates memory (caller must free), updates *rlen
static char *easy_mul(const size_t len1, const size_t len2, size_t *rlen) {
	if (len2 < len1) {
		return easy_mul(len2, len1, rlen);
	}

	*rlen = len1 + len2 - 1;
	char *ans = malloc(*rlen * sizeof(char));

	const size_t ind1 = len1 + 1;
	const size_t ind2 = len2 + 1;
	const size_t rem = ind1 % 2;

	for (size_t j = 0; j < 2 * ind1 - 4 - 2 * rem; j++) {
		if (j % 4 == 0) {
			ans[j] = ONE;
		} else {
			ans[j] = ZERO;
		}
	}

	if (ind2 >= ind1 && rem == 0) {
		ans[2 * ind1 - 4] = ONE;
	} else if (ind2 == ind1 && rem == 1) {
		ans[2 * ind1 - 6] = ONE;
		ans[2 * ind1 - 5] = ZERO;
		ans[2 * ind1 - 4] = ONE;
	} else {
		ans[2 * ind1 - 6] = ONE;
		ans[2 * ind1 - 5] = ZERO;
		ans[2 * ind1 - 4] = ZERO;
		ans[2 * ind1 - 3] = ONE;
	}

	for (size_t j = 1; j <= ind2 - ind1 - rem; j++) {
		ans[2 * ind1 - 4 + rem + j] = ZERO;
	}

	return ans;
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
			num1++;
		}
	}

	for (size_t i = 0; i < len2; ++i) {
		if (s2[i] == ONE) {
			num2++;
		}
	}

	size_t *lens1 = malloc(num1 * sizeof(size_t));
	size_t *lens2 = malloc(num2 * sizeof(size_t));

	for (size_t i = 0, j = 0; i < len1; i++) {
		if (s1[i] == ONE) {
			lens1[j] = len1 - i;
			j++;
		}
	}

	for (size_t i = 0, j = 0; i < len2; i++) {
		if (s2[i] == ONE) {
			lens2[j] = len2 - i;
			j++;
		}
	}

	zrep *zsum = malloc(sizeof(zrep));

	for (size_t k = num2 - 1; k >= 0; k--) {
		for (size_t j = num1 - 1; j >= 0; j--) {
			size_t summand_len;
			char *summand = easy_mul(lens1[j], lens2[k], &summand_len);
			if (k == num2 - 1 && j == num1 - 1) {
				zsum->val = summand;
				zsum->len = summand_len;
			} else {
				char *old = zsum->val;
				zsum->val = add_len(zsum->val, summand, zsum->len, summand_len, &zsum->len);
				free(old);
				free(summand);
			}
		}
	}

	// clean-up
	free(lens1);
	free(lens2);

	return zsum;
}
