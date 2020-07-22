#ifndef ZECKENDORF_H
#define ZECKENDORF_H

#include "types.h"
#include <stdbool.h>

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

// z_clear(z) frees the memory at z
// requires: z is non-NULL
void z_clear(zrep *z);

// z_rep(n) returns the Zeckendorf representation of n
// requires: n is non-NULL
// effects: allocates memory (caller must call z_clear)
zrep *z_rep(const zint *n);

#endif /* ZECKENDORF_H */
