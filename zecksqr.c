#include "zeckendorf.h"

bool zecksqr(const int n) {
	char *const rep = zeckendorf(n);
	const int len = strlen(rep);
	int i = 0;
	if (len % 2 != 0) {
		free(rep);
		return false;
	} else {
		for (i = 0; i < len / 2; i++) {
			if (rep[i] != rep[len / 2 + i]) {
				free(rep);
				return false;
			}
		}
	}
	free(rep);
	return true;
}
