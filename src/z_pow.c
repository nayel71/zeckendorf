#include "../include/zeckendorf.h"

int z_pow(const int n) {
	char *const rep = zeckendorf(n);
	const int len = strlen(rep);
	int pow = 1;
	for (int k = 2; k <= len / 2; k++) { // k is the number of blocks
		if (len % k == 0) {
			int block_size = len / k;
			for (int j = 0; j < block_size; j++) { // j traverses a single block
				for (int i = 0; i < k; i++) { // i traverses the blocks
					if (rep[i + j] != rep[i + j + block_size]) { // rep isn't an (i + 2)-power
						j = block_size;
						break;
					} else if (i == k - 2 && j == block_size - 1) {
						pow = k;
					}
				}
			}
		}
	}
	free(rep);
	return pow;
}
