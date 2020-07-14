#include "../include/zeckendorf.h"
#include "../include/arithmetic.h"
#include "add.h"
#include <stdlib.h>
#include <string.h>

// cf. paper by Frougny et al.

// add_same_len(z1, z2, len, rlen) returns the sum of z1 and z2 and stores its length at rlen if rlen != NULL
// requires: z1 and z2 are Zeckendorf representations with possible leading ZEROs, having equal length len
// effects: allocates memory (caller must free), updates *rlen if rlen != NULL
static zrep add_same_len(const zrep z1, const zrep z2, const int len, int *rlen) {
	const zdigit TWO = ONE + 1;
	const zdigit THREE = TWO + 1;

	if (z1[0] == ONE && z2[0] == ONE) {
		zrep cp1 = malloc((len + 2) * sizeof(zdigit));
		cp1[0] = ZERO;
		memcpy(cp1 + 1, z1, (len + 1) * sizeof(zdigit));

		zrep cp2 = malloc((len + 2) * sizeof(zdigit));
		cp2[0] = ZERO;
		memcpy(cp2 + 1, z2, (len + 1) * sizeof(zdigit));

		zrep ans = add_same_len(cp1, cp2, len + 1, rlen);
		free(cp1);
		free(cp2);
		return ans;
	}
	
	zrep ans = malloc((len + 2) * sizeof(zdigit)); 
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
	zdigit *pos = memchr(ans, ONE, (len + 1) * sizeof(zdigit));
	memmove(ans, pos, (len + 2 + ans - pos) * sizeof(zdigit));
	if (rlen) {
		*rlen = len + 1 + ans - pos;
	}
	return ans;
}

zrep add_len(const zrep z1, const zrep z2, const int len1, const int len2, int *rlen) {
	// add leading ZEROs to make lengths equal, then use add_same_len
	if (len1 > len2) {
		zrep cp = malloc((len1 + 1) * sizeof(zdigit));
		memset(cp, ZERO, (len1 - len2) * sizeof(zdigit));
		memcpy(cp + len1 - len2, z2, (len2 + 1) * sizeof(zdigit));
		zrep ans = add_same_len(z1, cp, len1, rlen);
		free(cp);
		return ans;
	} else if (len1 < len2) {
		return add_len(z2, z1, len2, len1, rlen);
	} else {
		return add_same_len(z1, z2, len1, rlen);
	}
}

zrep z_add(const zrep z1, const zrep z2) {
	return add_len(z1, z2, z_length(z1), z_length(z2), NULL);
}
