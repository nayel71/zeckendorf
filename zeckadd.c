#include "zeckendorf.h"
#include <stdio.h>

// digit constants:
const char zero = '0';
const char one = '1';
const char two = '2';
const char three = '3';

// cf. paper by Frougny et al.

// helper function:
// same_len(str1, str2) computes the Zeckendorf sum of the binary strings str1 and str2 that have the same length
// effects: allocates memory (caller must free)
// requires: str1, str2 are Zeckendorf representations
//           strlen(str1) = strlen(str2)
static char *same_len(const char *str1, const char *str2) {
	const int len = strlen(str1);
	char *ans;

	if (str1[0] == one && str2[0] == one) {
		char *new1 = malloc((len + 2) * sizeof(char));
		char *new2 = malloc((len + 2) * sizeof(char));
		new1[0] = zero;
		new1[1] = '\0';
		new2[0] = zero;
		new2[1] = '\0';
		strcat(new1, str1);
		strcat(new2, str2);
		ans = same_len(new1, new2);
		free(new1);
		free(new2);
		return ans;
	}
	
	ans = malloc((len + 2) * sizeof(char)); 
	ans[0] = zero; 
	
	// add pointwise
	for (int i = 1; i <= len; i++) {
		if (str1[i - 1] != str2[i - 1]) {
			ans[i] = one;
		} else if (str1[i - 1] == str2[i - 1] && str1[i - 1] == one) {
			ans[i] = two;
		} else {
			ans[i] = zero;
		}
	}

	// first stage

	// eliminate 2's
	for (int i = 0; i < len - 2; i++) {
		if (ans[i] == zero && ans[i + 1] == two && ans[i + 2] == zero) {
			ans[i] = one;
			ans[i + 1] = zero;
			ans[i + 2] = zero;
			ans[i + 3] += 1;
		} else if (ans[i] == zero && ans[i + 1] == three && ans[i + 2] == zero) {
			ans[i] = one;
			ans[i + 1] = one;
			ans[i + 2] = zero;
			ans[i + 3] += 1;
		} else if (ans[i] == zero && ans[i + 1] == two && ans[i + 2] == one) {
			ans[i] = one;
			ans[i + 1] = one;
			ans[i + 2] = zero;
		} else if (ans[i] == zero && ans[i + 1] == one && ans[i + 2] == two) {
			ans[i] = one;
			ans[i + 1] = zero;
			ans[i + 2] = one;
		} 

		if (ans[len - 2] == zero && ans[len - 1] == two && ans[len] == one) {
			ans[len - 2] = one;
			ans[len - 1] = one;
			ans[len] = zero;
		} else if (ans[len - 2] == zero && ans[len - 1] == one && ans[len] == two) {
			ans[len - 2] = one;
			ans[len - 1] = zero;
			ans[len] = one;
		} 
	}

	// clean-up
	if (ans[len - 2] == zero && ans[len - 1] == three && ans[len] == zero) {
		ans[len - 2] = one;
		ans[len - 1] = one;
		ans[len] = one;
	} else if (ans[len - 2] == zero && ans[len - 1] == two && ans[len] == zero) {
		ans[len - 2] = one;
		ans[len - 1] = zero;
		ans[len] = one;
	} else if (len > 2 && ans[len - 3] == zero && ans[len - 2] == one && ans[len - 1] == two && ans[len] == zero) {
		ans[len - 3] = one;
		ans[len - 2] = zero;
		ans[len - 1] = one;
		ans[len] = zero;
	} else if (ans[len - 1] == zero && ans[len] == three) {
		ans[len - 1] = one;
		ans[len] = one;
	} else if (ans[len - 1] == zero && ans[len] == two) {
		ans[len - 1] = one;
		ans[len] = zero;
	} else if (ans[len - 2] == zero && ans[len - 1] == one && ans[len] == two) {
		ans[len - 2] = one;
		ans[len - 1] = zero;
		ans[len] = one;
	}

	// second stage
	
	// first pass from right to left
	for (int i = len; i >= 2; i--) {
		if (ans[i] == one && ans[i - 1] == one && ans[i - 2] == zero) {
			ans[i] = zero;
			ans[i - 1] = zero;
			ans[i - 2] = one;
		}
	}

	// second pass from left to right
	for (int i = 0; i <= len - 2; i++) {
		if (ans[i] == zero && ans[i + 1] == one && ans[i + 2] == one) {
			ans[i] = one;
			ans[i + 1] = zero;
			ans[i + 2] = zero;
		}
	}

	ans[len + 1] = '\0';
	char *ans2 = malloc((len + 2) * sizeof(char));
	strcpy(ans2, memchr(ans, one, len + 1));
	free(ans);
	return ans2; 
}

char *zeck_add(const char *str1, const char *str2) {
	const int len1 = strlen(str1);
	const int len2 = strlen(str2);
	char *new = malloc((len1 + len2 + 1) * sizeof(char));
	char *ans;

	// add leading zeros to make lengths equal, then use helper function
	if (len1 > len2) {
		for (int i = 0; i < len1 - len2; i++) {
			new[i] = zero;
		}
		new[len1 - len2] = '\0';
		strcat(new, str2);
		ans = same_len(str1, new);
	} else if (len1 < len2) {
		for (int i = 0; i < len2 - len1; i++) {
			new[i] = zero;
		}
		new[len2 - len1] = '\0';
		strcat(new, str1);
		ans = same_len(new, str2);
	} else { 
		ans = same_len(str1, str2);
	}

	free(new);
	return ans;
}
