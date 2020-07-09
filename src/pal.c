#include "../include/zeckendorf.h"
#include <stdlib.h>

bool z_pal(const zint n) {
	zrep const rep = z_rep(n);
	if (rep) {
		int len = z_length(rep);
		for (int i = 0; i < len / 2; i++) {
			if (rep[i] != rep[len - i - 1]) {
				free(rep);
				return false;
			}
		}
		free(rep);
		return true;
	} else { // should not get here
		return false;
	}
}
