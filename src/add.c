#include "../include/zeckendorf.h"

// digit constants:
const char ZERO = '0';
const char ONE = '1';
static const char TWO = '2';
static const char THREE = '3';

// cf. paper by Frougny et al.

// add_same_len(str1, str2, len) returns the Zeckendorf sum of the binary strings str1 and str2
// effects: allocates memory (caller must free)
// requires: len == strlen(str1) == strlen(str2)
static char *add_same_len(const char *str1, const char *str2, const int len) {
	if (str1[0] == ONE && str2[0] == ONE) {
		char *cpy1 = malloc((len + 2) * sizeof(char));
		cpy1[0] = ZERO;
		memcpy(cpy1 + 1, str1, len + 1);
		char *cpy2 = malloc((len + 2) * sizeof(char));
		cpy2[0] = ZERO;
		memcpy(cpy2 + 1, str2, len + 1);
		char *ans = add_same_len(cpy1, cpy2, len + 1);
		free(cpy1);
		free(cpy2);
		return ans;
	}
	
	char *ans = malloc((len + 2) * sizeof(char)); 
	ans[0] = ZERO; 
	ans[len + 1] = '\0';
	
	// add pointwise
	for (int i = 1; i <= len; i++) {
		if (str1[i - 1] != str2[i - 1]) {
			ans[i] = ONE;
		} else if (str1[i - 1] == str2[i - 1] && str1[i - 1] == ONE) {
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
	char *pos = memchr(ans, ONE, len + 1);
	memmove(ans, pos, len + 2 + ans - pos);
	return ans;
}

char *add(const char *str1, const char *str2) {
	const int len1 = strlen(str1);
	const int len2 = strlen(str2);

	// add leading ZEROs to make lengths equal, then use add_same_len
	if (len1 > len2) {
		char *cpy = malloc((len1 + 1) * sizeof(char));
		memset(cpy, ZERO, len1 - len2);
		memcpy(cpy + len1 - len2, str2, len2 + 1);
		char *ans = add_same_len(str1, cpy, len1);
		free(cpy);
		return ans;
	} else if (len1 < len2) { 
		char *cpy = malloc((len2 + 1) * sizeof(char));
		memset(cpy, ZERO, len2 - len1);
		memcpy(cpy + len2 - len1, str1, len1 + 1);
		char *ans = add_same_len(cpy, str2, len2);
		free(cpy);
		return ans;
	} else {
		return add_same_len(str1, str2, len1);
	}
}
