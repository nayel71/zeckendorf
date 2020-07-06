#include "add.h"
#include "../include/zeckendorf.h"
#include <stdlib.h>
#include <string.h>

// cf. the paper by Frougny et al.

// add_same_len(z1, z2, len, res_len) returns the sum of z1 and z2 and stores its length and res_len
// requires: z1 and z2 are Zeckendorf representations with possible leading ZEROs having equal length len
// effects: allocates memory (caller must free), updates res_len if res_len != NULL
static z_rep add_same_len(const z_rep z1, const z_rep z2, const int len, int *res_len) {
	const z_digit TWO = ONE + 1;
	const z_digit THREE = TWO + 1;

	if (z1[0] == ONE && z2[0] == ONE) {
		z_rep cp1 = malloc((len + 2) * sizeof(z_digit));
		cp1[0] = ZERO;
		memcpy(cp1 + 1, z1, (len + 1) * sizeof(z_digit));

		z_rep cp2 = malloc((len + 2) * sizeof(z_digit));
		cp2[0] = ZERO;
		memcpy(cp2 + 1, z2, (len + 1) * sizeof(z_digit));

		z_rep ans = add_same_len(cp1, cp2, len + 1, res_len);
		free(cp1);
		free(cp2);
		return ans;
	}
	
	z_rep ans = malloc((len + 2) * sizeof(z_digit)); 
	ans[0] = ZERO; 
	ans[len + 1] = '\0';
	
	// add pointwise
	for (int i = 1; i <= len; i++) {
		if (z1[i - 1] != z2[i - 1]) {
			ans[i] = ONE;
		} else if (z1[i - 1] == z2[i - 1] && z1[i - 1] == ONE) {
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
	z_digit *pos = memchr(ans, ONE, (len + 1) * sizeof(z_digit));
	memmove(ans, pos, (len + 2 + ans - pos) * sizeof(z_digit));
	if (res_len) {
		*res_len = len + 1 + ans - pos;
	}
	return ans;
}

z_rep add_len(const z_rep z1, const z_rep z2, const int len1, const int len2, int *len) {
	// add leading ZEROs to make lengths equal, then use add_same_len
	if (len1 > len2) {
		z_rep cp = malloc((len1 + 1) * sizeof(z_digit));
		memset(cp, ZERO, (len1 - len2) * sizeof(z_digit));
		memcpy(cp + len1 - len2, z2, (len2 + 1) * sizeof(z_digit));
		z_rep ans = add_same_len(z1, cp, len1, len);
		free(cp);
		return ans;
	} else if (len1 < len2) {
		return add_len(z2, z1, len2, len1, len);
	} else {
		return add_same_len(z1, z2, len1, len);
	}
}

z_rep z_add(const z_rep z1, const z_rep z2) {
	int len1, len2;
	if (!z_rep_is_valid(z1, &len1, false)) {
		exit(z_error(REP, z1));
	} else if (!z_rep_is_valid(z2, &len2, false)) {
		exit(z_error(REP, z2));
	} else {
		return add_len(z1, z2, len1, len2, NULL);
	}
}
