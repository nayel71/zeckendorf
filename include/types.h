#ifndef TYPES_H
#define TYPES_H

// constants:
extern const long long LIMIT;
extern const char ZERO;
extern const char ONE;

typedef struct {
	long long val;
} zint;

typedef struct {
	char *val; // a char array, not a string
	int len; // length of the char array
} zrep;

#endif /* TYPES_H */
