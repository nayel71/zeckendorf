#include "../include/zeckendorf.h"
#include "../include/arithmetic.h"
#include "add.h"
#include <stdlib.h>
#include <string.h>

// easy_mul(s1, s2, len1, len2, rlen) returns the string representation of the product of the
// Zeckendorf representations given by s1 and s2, and stores its length at rlen
// requires: strlen(s1) == len1 && strlen(s2) == len2 && rlen != NULL, s1 and s2 each contain a single ONE
// effects: allocates memory (caller must free), updates *rlen
static char *easy_mul(const char *s1, const char *s2, const int len1, const int len2, int *rlen) {
	if (len2 < len1) {
		return easy_mul(s2, s1, len2, len1, rlen);
	}

	*rlen = len1 + len2 - 1;
	char *ans = malloc((*rlen + 1) * sizeof(char));
	ans[*rlen] = '\0';

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

zrep z_mul(const zrep z1, const zrep z2) {
	// split z1 and z2 into sums of Fibonacci numbers, then multiply everything out
	char *s1 = zrtostr(z1);
	char *s2 = zrtostr(z2);
	int len1 = 0;
	int len2 = 0;

	int n1 = 0; // number of ONEs in z1
	int n2 = 0; // number of ONEs in z2

	for (int i = 0; s1[i]; ++len1, ++i) {
		if (s1[i] == ONE) {
			n1++;
		} 
	}

	for (int i = 0; s2[i]; ++len2, ++i) {
		if (s2[i] == ONE) {
			n2++;
		} 
	}

	char **fibs1 = malloc(n1 * sizeof(char *));
	char **fibs2 = malloc(n2 * sizeof(char *));
	int *lens1 = malloc(n1 * sizeof(int));
	int *lens2 = malloc(n2 * sizeof(int));

	for (int i = 0, m1 = 0; i < len1; i++) {
		if (s1[i] == ONE) {
			lens1[m1] = len1 - i;
			fibs1[m1] = malloc((lens1[m1] + 1) * sizeof(char));
			fibs1[m1][0] = ONE;
			memset(fibs1[m1] + 1, ZERO, (lens1[m1] - 1) * sizeof(char));
			fibs1[m1][lens1[m1]] = '\0';
			m1++;
		}
	}

	for (int i = 0, m2 = 0; i < len2; i++) {
		if (s2[i] == ONE) {
			lens2[m2] = len2 - i;
			fibs2[m2] = malloc((lens2[m2] + 1) * sizeof(char));
			fibs2[m2][0] = ONE;
			memset(fibs2[m2] + 1, ZERO, (lens2[m2] - 1) * sizeof(char));
			fibs2[m2][lens2[m2]] = '\0';
			m2++;
		}
	}

	char *sum;
	int sum_len;
	for (int k = n2 - 1; k >= 0; k--) {
		for (int j = n1 - 1; j >= 0; j--) {
			int summand_len;
			char *summand = easy_mul(fibs1[j], fibs2[k], lens1[j], lens2[k], &summand_len);
			if (k == n2 - 1 && j == n1 - 1) {
				sum_len = summand_len;
				sum = malloc((sum_len + 1) * sizeof(char));
				memcpy(sum, summand, (summand_len + 1) * sizeof(char));
			} else {
				char *temp = add_len(sum, summand, sum_len, summand_len, &sum_len);
				sum = realloc(sum, (sum_len + 1) * sizeof(char));
				memcpy(sum, temp, (sum_len + 1) * sizeof(char));
				free(temp);
			}
			free(summand);
		}
	}

	// clean-up
	free(s1);
	free(s2);

	for (int i = 0; i < n1; i++) {
		free(fibs1[i]);
	}

	for (int i = 0; i < n2; i++) {
		free(fibs2[i]);
	}

	free(fibs1);
	free(fibs2);
	free(lens1);
	free(lens2);

	zrep zsum = strtozr(sum);
	free(sum);
	return zsum;
}
