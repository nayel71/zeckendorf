#include "../include/zeckendorf.h"
#include "add.h"
#include <stdlib.h>
#include <string.h>

// easy_mul(str1, str2, len1, len2, len) returns the product of str1 and str2 and stores its length at len
// requires: str1 and str2 are Zeckendorf representations containing a single ONE, len1 == strlen(str1), len2 == strlen(str2)
// effects: allocates memory (caller must free), updates len
static z_rep easy_mul(const z_rep str1, const z_rep str2, const int len1, const int len2, int *len) {
	if (len2 < len1) {
		return easy_mul(str2, str1, len2, len1, len);
	}

	*len = len1 + len2 - 1;
	z_rep ans = malloc((*len + 1) * sizeof(ZERO));
	ans[*len] = '\0';

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

z_rep z_mul(const z_rep str1, const z_rep str2) {
	if (!z_rep_is_valid(str1)) {
		exit(z_error(REP, str1));
	} else if (!z_rep_is_valid(str2)) {
		exit(z_error(REP, str2));
	}

	const int len1 = strlen(str1) + 1;
	const int len2 = strlen(str2) + 1;
	z_digit fib1[len1 / 2][len1];
	z_digit fib2[len2 / 2][len2];
	int lengths1[len1 / 2];
	int lengths2[len2 / 2];
	int n1 = 0; // number of ONEs in str1
	int n2 = 0; // number of ONEs in str2

	// split first string into a sum of Fibonacci numbers
	for (int i = 0; i < len1; i++) {
		if (str1[i] == ONE) {
			fib1[n1][0] = ONE;
			lengths1[n1] = len1 - i - 1;
			memset(fib1[n1] + 1, ZERO, lengths1[n1]);
			fib1[n1][lengths1[n1]] = '\0';
			n1++;
		} 
	}

	// split second string into a sum of Fibonacci numbers
	for (int i = 0; i < len2; i++) {
		if (str2[i] == ONE) {
			fib2[n2][0] = ONE;
			lengths2[n2] = len2 - i - 1;
			memset(fib2[n2] + 1, ZERO, lengths2[n2]);
			fib2[n2][lengths2[n2]] = '\0';
			n2++;
		} 
	}

	// multiply everything out
	z_rep sum = malloc((len1 + len2) * sizeof(ZERO));

	for (int k = n2 - 1; k >= 0; k--) {
		for (int j = n1 - 1; j >= 0; j--) {
			int sum_len, summand_len;
			z_rep summand = easy_mul(fib1[j], fib2[k], lengths1[j], lengths2[k], &summand_len);
			if (k == n2 - 1 && j == n1 - 1) {
				memcpy(sum, summand, summand_len + 1);
				sum_len = summand_len;
			} else {
				z_rep temp = add_len(sum, summand, sum_len, summand_len, &sum_len);
				memcpy(sum, temp, sum_len + 1);
				free(temp);
			}
			free(summand);
		}
	}

	return sum;
}
