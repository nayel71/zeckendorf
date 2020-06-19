#include "../include/zeckendorf.h"

// easy_mult(str1, str2, len1, len2) returns the Zeckendorf product of the binary strings
// str1 and str2 of the form 0...010...0 of lengths len1 and len2 respectively
// effects: allocates memory (caller must free)
static char *easy_mult(const char *str1, const char *str2, int len1, int len2) {
	if (len2 < len1) {
		return easy_mult(str2, str1, len2, len1);
	}

	char *ans = malloc((len1 + len2) * sizeof(char));
	const int ind1 = len1 + 1;
	const int ind2 = len2 + 1;
	ans[ind1 + ind2 - 3] = '\0';

	if (ind2 >= ind1 && ind1 >= 2 && ind1 % 2 == 0) {
		for (int j = 0; j < 2 * ind1 - 4; j++) {
			if (j % 4 == 0) {
				ans[j] = ONE;
			} else {
				ans[j] = ZERO;
			}
		}
		ans[2 * ind1 - 4] = ONE;
		for (int j = 1; j <= ind2 - ind1; j++) {
			ans[2 * ind1 - 4 + j] = ZERO;
		}
	} else if (ind2 == ind1 && ind1 % 2 == 1) {
		for (int j = 0; j < 2 * ind1 - 6; j++) {
			if (j % 4 == 0) {
				ans[j] = ONE;
			} else {
				ans[j] = ZERO;
			}
		}
		ans[2 * ind1 - 6] = ONE;
		ans[2 * ind1 - 5] = ZERO;
		ans[2 * ind1 - 4] = ONE;
	} else if (ind2 >= ind1 + 1 && ind1 >= 2 && ind1 % 2 == 1) {
		for (int j = 0; j < 2 * ind1 - 6; j++) {
			if (j % 4 == 0) {
				ans[j] = ONE;
			} else {
				ans[j] = ZERO;
			}
		}
		ans[2 * ind1 - 6] = ONE;
		ans[2 * ind1 - 5] = ZERO;
		ans[2 * ind1 - 4] = ZERO;
		ans[2 * ind1 - 3] = ONE;
		for (int j = 1; j <= ind2 - ind1 - 1; j++) {
			ans[2 * ind1 - 3 + j] = ZERO;
		}
	}

	return ans;
}

char *mult(const char *str1, const char *str2) {
	const int len1 = strlen(str1) + 1;
	const int len2 = strlen(str2) + 1;
	int lengths1[len1 / 2];
	int lengths2[len2 / 2];
	char fib1[len1 / 2][len1];
	char fib2[len2 / 2][len2];

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
	char *sum = malloc((len1 + len2) * sizeof(char));
	for (int k = n2 - 1; k >= 0; k--) {
		for (int j = n1 - 1; j >= 0; j--) {
			char *summand = easy_mult(fib1[j], fib2[k], lengths1[j], lengths2[k]);
			if (k == n2 - 1 && j == n1 - 1) {
				strcpy(sum, summand);
			} else {
				char *temp = add(sum, summand);
				strcpy(sum, temp);
				free(temp);
			}
			free(summand);
		}
	}

	return sum;
}
