#include "../include/zeckendorf.h"
#include "../include/arithmetic.h"
#include "add.h"
#include <stdlib.h>
#include <string.h>

// easy_mul(len1, len2, rlen) returns a char array representing the product of Zeckendorf representations
// of lengths len1 and len2 each containing a single ONE, and stores its length at rlen
// requires: rlen != NULL
// effects: allocates memory (caller must free), updates *rlen
static char *easy_mul(const int len1, const int len2, int *rlen) {
	if (len2 < len1) {
		return easy_mul(len2, len1, rlen);
	}

	*rlen = len1 + len2 - 1;
	char *ans = malloc(*rlen * sizeof(char));

	const int ind1 = len1 + 1;
	const int ind2 = len2 + 1;
	const int rem = ind1 % 2;

	for (int j = 0; j < 2 * ind1 - 4 - 2 * rem; j++) {
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

	for (int j = 1; j <= ind2 - ind1 - rem; j++) {
		ans[2 * ind1 - 4 + rem + j] = ZERO;
	}

	return ans;
}

zrep *z_mul(const zrep *z1, const zrep *z2) {
	// split z1 and z2 into sums of Fibonacci numbers, then multiply everything out
	char *s1 = z1->val;
	char *s2 = z2->val;
	int len1 = z1->len;
	int len2 = z2->len;
	int num1 = 0; // number of ONEs in z1
	int num2 = 0; // number of ONEs in z2

	for (int i = 0; i < len1; ++i) {
		if (s1[i] == ONE) {
			num1++;
		}
	}

	for (int i = 0; i < len2; ++i) {
		if (s2[i] == ONE) {
			num2++;
		}
	}

	int *lens1 = malloc(num1 * sizeof(int));
	int *lens2 = malloc(num2 * sizeof(int));

	for (int i = 0, j = 0; i < len1; i++) {
		if (s1[i] == ONE) {
			lens1[j] = len1 - i;
			j++;
		}
	}

	for (int i = 0, j = 0; i < len2; i++) {
		if (s2[i] == ONE) {
			lens2[j] = len2 - i;
			j++;
		}
	}

	zrep *zsum = malloc(sizeof(zrep));

	for (int k = num2 - 1; k >= 0; k--) {
		for (int j = num1 - 1; j >= 0; j--) {
			int summand_len;
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
