#include "../include/zeckendorf.h"
#include <stdlib.h>
#include <string.h>

bool z_pal(const z_int n) {
	z_rep const rep = zeckendorf(n);
	const int len = strlen(rep);
	for (int i = 0; i < len / 2; i++) {
		if (rep[i] != rep[len - i - 1]) {
			free(rep);
			return false;
		}
	}
	free(rep);
	return true;
}
