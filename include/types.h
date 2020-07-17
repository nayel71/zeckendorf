#ifndef TYPES_H
#define TYPES_H

#include <stddef.h>

// constants:
extern const long long LIMIT;
extern const char ZERO;
extern const char ONE;

typedef struct zint {
	long long val;
} zint;

typedef struct zrep {
	char *val;
	size_t len;
} zrep;

#endif /* TYPES_H */
