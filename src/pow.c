#include "../include/zeckendorf.h"
#include <stdlib.h>
#include <string.h>

int z_pow(const z_int n) {
	z_rep const rep = zeckendorf(n);
	int len;
	if (z_rep_is_valid(rep, &len, false)) {
		int pow = 1;
		for (int k = 2; k <= len / 2; k++) { // k is the number of blocks
			if (len % k == 0) {
				int d = len / k; // block size
				for (int j = 0; j < d; j++) { // j traverses a single block
					for (int i = 0; i < k - 1; i++) { // i traverses the blocks
						if (rep[j + i * d] != rep[j + (i + 1) * d]) { // rep isn't an (i + 2)-power
							j = d;
							break;
						} else if (i == k - 2 && j == d - 1) {
							pow = k;
						}
					}
				}
			}
		}
		free(rep);
		return pow;
	}
	// we should not get here
	free(rep);
	exit(z_error(REP, rep));
}
