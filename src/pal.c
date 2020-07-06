#include "../include/zeckendorf.h"
#include <stdlib.h>

bool z_pal(const z_int n) {
	z_rep const rep = zeckendorf(n);
	int len;
	if (z_rep_is_valid(rep, &len, false)) {
		for (int i = 0; i < len / 2; i++) {
			if (rep[i] != rep[len - i - 1]) {
				free(rep);
				return false;
			}
		}
		free(rep);
		return true;
	}
	// should not get here
	free(rep);
	exit(z_error(REP, rep));
}
