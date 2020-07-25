#ifndef ZECKENDORF_H
#define ZECKENDORF_H

#include <stdbool.h>

// constants:
extern const long long LIMIT;
extern const char ZERO;
extern const char ONE;

typedef struct zint zint;
typedef struct zrep zrep;

// definitions:
// - a zint * is a return value of strtozi
// - a zrep * is a return value of strtozr

// informally,
// - a zint represents a positive integer <= LIMIT
// - a zrep represents a string of ZEROs and ONEs starting with ONE,
//   that does not contain consecutive ONEs

// strtozi(s) tries to convert s to a non-NULL zint *
// returns the converted value if successful, returns NULL otherwise
// effects: allocates memory (caller must free)
zint *strtozi(const char *s);

// strtozr(s) tries to convert s to a non-NULL zrep *
// returns the converted value if successful, returns NULL otherwise
// effects: allocates memory (caller must call z_clear)
zrep *strtozr(const char *s);

// zrtostr(z) converts z to a string
// requires: z is non-NULL
// effects: allocates memory (caller must free)
char *zrtostr(const zrep *z);

// z_clear(z) frees all memory associated with z
// requires: z is non-NULL
// effects: memory associated with z is invalid
void z_clear(zrep *z);

// z_rep(n) returns the Zeckendorf representation of n
// requires: n is non-NULL
// effects: allocates memory (caller must call z_clear)
zrep *z_rep(const zint *n);

#endif /* ZECKENDORF_H */
