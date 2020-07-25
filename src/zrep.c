#include "zrep.h"
#include <stdlib.h>

struct zrep {
	char *val; // a char array, not a string
	size_t len; // length of the char array
};

zrep *zrep_new(char *arr, size_t len) {
	zrep *z = malloc(sizeof(zrep));
	z->val = arr;
	z->len = len;
	return z;
}

char *zrep_arr(const zrep *z) {
	return z->val;
}

size_t zrep_len(const zrep *z) {
	return z->len;
}

void zrep_free(zrep *z) {
	free(z->val);
	free(z);
}
