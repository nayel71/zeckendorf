#include "../include/zeckendorf.h"
#include "../include/arithmetic.h"
#include "add.h"
#include <stdlib.h>
#include <string.h>

// easy_mul(s1, s2, len1, len2, rlen) returns a char array representing the product of Zeckendorf representations
// given by s1 and s2, and stores its length at rlen
// requires: s1 and s2 represent Zeckendorf representations of lengths len1 and len2 respectively each containing
// a single ONE, rlen != NULL
// effects: allocates memory (caller must free), updates *rlen
static char *easy_mul(const char *s1, const char *s2, size_t len1, size_t len2, size_t *rlen) {
	if (len2 < len1) {
		return easy_mul(s2, s1, len2, len1, rlen);
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

	char **fibs1 = malloc(num1 * sizeof(char *));
	char **fibs2 = malloc(num2 * sizeof(char *));
	int *lens1 = malloc(num1 * sizeof(int));
	int *lens2 = malloc(num2 * sizeof(int));

	for (int i = 0, j = 0; i < len1; i++) {
		if (s1[i] == ONE) {
			lens1[j] = len1 - i;
			fibs1[j] = malloc(lens1[j] * sizeof(char));
			fibs1[j][0] = ONE;
			memset(fibs1[j] + 1, ZERO, (lens1[j] - 1) * sizeof(char));
			j++;
		}
	}

	for (int i = 0, j = 0; i < len2; i++) {
		if (s2[i] == ONE) {
			lens2[j] = len2 - i;
			fibs2[j] = malloc(lens2[j] * sizeof(char));
			fibs2[j][0] = ONE;
			memset(fibs2[j] + 1, ZERO, (lens2[j] - 1) * sizeof(char));
			j++;
		}
	}

	zrep *zsum = malloc(sizeof(zrep));

	for (int k = num2 - 1; k >= 0; k--) {
		for (int j = num1 - 1; j >= 0; j--) {
			size_t summand_len;
			char *summand = easy_mul(fibs1[j], fibs2[k], lens1[j], lens2[k], &summand_len);
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
	for (int i = 0; i < num1; i++) {
		free(fibs1[i]);
	}

	for (int i = 0; i < num2; i++) {
		free(fibs2[i]);
	}

	free(fibs1);
	free(fibs2);
	free(lens1);
	free(lens2);

	return zsum;
}
