#include "../include/zeckendorf.h"
#include <stdlib.h>

int z_pow(const zint n) {
	zrep const rep = z_rep(n);
	if (zrep_is_valid(rep)) {
		int len = z_length(rep);
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
	} else {
		free(rep);
		exit(z_error(REP, rep));
	}
}
