#include "zeckendorf.h"

// helper function:
// easy_mult(str1, str2) returns the Zeckendorf product of the simple binary strings str1 and str2 of the form 0...010...0
// effects: allocates memory (caller must free)
static char *easy_mult(const char *str1, const char *str2) {
	const int len1 = strlen(str1);
	const int len2 = strlen(str2);

	char *ans = malloc((len1 + len2) * sizeof(char));
	const int ind1 = len1 + 1;
	const int ind2 = len2 + 1;
	ans[ind1 + ind2 - 3] = '\0';

	if (ind2 >= ind1 && ind1 >= 2 && ind1 % 2 == 0) {
		for (int j = 0; j < 2 * ind1 - 4; j++) {
			if (j % 4 == 0) {
				ans[j] = one;
			} else {
				ans[j] = zero;
			}
		}
		ans[2 * ind1 - 4] = one;
		for (int j = 1; j <= ind2 - ind1; j++) {
			ans[2 * ind1 - 4 + j] = zero;
		}
	} else if (ind2 == ind1 && ind1 % 2 == 1) {
		for (int j = 0; j < 2 * ind1 - 6; j++) {
			if (j % 4 == 0) {
				ans[j] = one;
			} else {
				ans[j] = zero;
			}
		}
		ans[2 * ind1 - 6] = one;
		ans[2 * ind1 - 5] = zero;
		ans[2 * ind1 - 4] = one;
	} else if (ind2 >= ind1 + 1 && ind1 >= 2 && ind1 % 2 == 1) {
		for (int j = 0; j < 2 * ind1 - 6; j++) {
			if (j % 4 == 0) {
				ans[j] = one;
			} else {
				ans[j] = zero;
			}
		}
		ans[2 * ind1 - 6] = one;
		ans[2 * ind1 - 5] = zero;
		ans[2 * ind1 - 4] = zero;
		ans[2 * ind1 - 3] = one;
		if (ind2 - ind1 - 1 >= 1) {
			for (int j = 1; j <= ind2 - ind1 - 1; j++) {
				ans[2 * ind1 - 3 + j] = zero;
			}
		}
	} else if (ind2 < ind1) {
		free(ans);
		return easy_mult(str2, str1);
	}

	return ans;
}

char *zeck_mult(const char *str1, const char *str2) {
	const int len1 = strlen(str1) + 1;
	const int len2 = strlen(str2) + 1;
	int lengths1[len1/2];
	int lengths2[len2/2];
	char fib1[len1/2][len1];
	char fib2[len2/2][len2];

	int n1 = 0; // number of ones in str1
	int n2 = 0; // number of ones in str2

	// split first string into sum of Fibonacci numbers
	for (int i = 0; i < len1; i++) {
		if (str1[i] == one) {
			fib1[n1][0] = one;
			lengths1[n1] = len1 - i - 1;
			for (int j = 1; j < lengths1[n1]; j++) {
				fib1[n1][j] = zero;
			}
			fib1[n1][lengths1[n1]] = '\0';
			n1++;
		} 
	}

	// split second string into sum of Fibonacci numbers
	for (int i = 0; i < len2; i++) {
		if (str2[i] == one) {
			fib2[n2][0] = one;
			lengths2[n2] = len2 - i - 1;
			for (int j = 1; j < lengths2[n2]; j++) {
				fib2[n2][j] = zero;
			}
			fib2[n2][lengths2[n2]] = '\0';
			n2++;
		} 
	}

	// multiply everything out
	char *sum = malloc((len1 + len2) * sizeof(char));
	for (int k = n2 - 1; k >= 0; k--) {
		for (int j = n1 - 1; j >= 0; j--) {
			char *summand = easy_mult(fib1[j], fib2[k]);
			if (k == n2 - 1 && j == n1 - 1) {
				strcpy(sum, summand);
			} else {
				char *temp = zeck_add(sum, summand);
				strcpy(sum, temp);
				free(temp);
			}
			free(summand);
		}
	}

	return sum;
}
