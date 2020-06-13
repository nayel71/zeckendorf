#include "../include/zeckendorf.h"

bool is_sqr(const int n) {
	char *const rep = zeckendorf(n);
	const int len = strlen(rep);
	if (len % 2 != 0) {
		free(rep);
		return false;
	} else {
		for (int i = 0; i < len / 2; i++) {
			if (rep[i] != rep[len / 2 + i]) {
				free(rep);
				return false;
			}
		}
	}
	free(rep);
	return true;
}
