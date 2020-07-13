#include "../include/zeckendorf.h"
#include <stdlib.h>

bool z_pal(const zint n) {
	zrep rep = z_rep(n);
	int len = z_length(rep);
	for (int i = 0; i < len / 2; i++) {
		if (rep[i] != rep[len - i - 1]) {
			z_clear(&rep);
			return false;
		}
	}
	z_clear(&rep);
	return true;
}
