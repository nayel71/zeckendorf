#include "../include/zeckendorf.h"

bool is_pal(const int n) {
	char *const rep = zeckendorf(n);
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
