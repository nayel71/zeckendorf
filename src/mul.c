#include "../include/arithmetic.h"
#include "add.h"
#include <stdlib.h>
#include <string.h>

// easy_mul(z1, z2, len1, len2, len) returns the product of z1 and z2 and stores its length at len
// requires: zrep_is_valid(z1) && zrep_is_valid(z2) && z_length(z1) == len1 && z_length(z2) == len2 && len;
// furthermore, z1 and z2 each contain a single ONE
// effects: allocates memory (caller must free), updates *len
static zrep easy_mul(const zrep z1, const zrep z2, const int len1, const int len2, int *len) {
	if (len2 < len1) {
		return easy_mul(z2, z1, len2, len1, len);
	}

	*len = len1 + len2 - 1;
	zrep ans = malloc((*len + 1) * sizeof(zdigit));
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

zrep z_mul(const zrep z1, const zrep z2) {
	if (!zrep_is_valid(z1) || !zrep_is_valid(z2)) {
		return NULL;
	}

	int len1 = z_length(z1) + 1;
	int len2 = z_length(z2) + 1;
	zdigit fib1[len1 / 2][len1];
	zdigit fib2[len2 / 2][len2];
	int lengths1[len1 / 2];
	int lengths2[len2 / 2];
	int n1 = 0; // number of ONEs in z1
	int n2 = 0; // number of ONEs in z2

	// split first string into a sum of Fibonacci numbers
	for (int i = 0; i < len1; i++) {
		if (z1[i] == ONE) {
			fib1[n1][0] = ONE;
			lengths1[n1] = len1 - i - 1;
			memset(fib1[n1] + 1, ZERO, lengths1[n1] * sizeof(zdigit));
			fib1[n1][lengths1[n1]] = '\0';
			n1++;
		} 
	}

	// split second string into a sum of Fibonacci numbers
	for (int i = 0; i < len2; i++) {
		if (z2[i] == ONE) {
			fib2[n2][0] = ONE;
			lengths2[n2] = len2 - i - 1;
			memset(fib2[n2] + 1, ZERO, lengths2[n2] * sizeof(zdigit));
			fib2[n2][lengths2[n2]] = '\0';
			n2++;
		} 
	}

	// multiply everything out
	zrep sum = malloc((len1 + len2) * sizeof(zdigit));
	int sum_len;
	int summand_len;
	for (int k = n2 - 1; k >= 0; k--) {
		for (int j = n1 - 1; j >= 0; j--) {
			zrep summand = easy_mul(fib1[j], fib2[k], lengths1[j], lengths2[k], &summand_len);
			if (k == n2 - 1 && j == n1 - 1) {
				memcpy(sum, summand, (summand_len + 1) * sizeof(zdigit));
				sum_len = summand_len;
			} else {
				zrep temp = add_len(sum, summand, sum_len, summand_len, &sum_len);
				memcpy(sum, temp, (sum_len + 1) * sizeof(zdigit));
				free(temp);
			}
			free(summand);
		}
	}

	return sum;
}
