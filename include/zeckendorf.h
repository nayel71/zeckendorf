#ifndef ZECKENDORF_H
#define ZECKENDORF_H

#include "types.h"
#include <stdbool.h>

// definitions:
// - a zint * is either NULL or a non-NULL return value of strtozi
// - a zrep * is either NULL or a non-NULL return value of strtozr

// informally,
// - a zint represents a non-negative integer <= LIMIT
// - a zrep represents a binary string consisting of ZEROs and ONEs,
//   that starts with ONE and does not contain consecutive ONEs

// strtozi(str) tries to convert str to a non-NULL zint *
// returns the converted value if successful, returns NULL otherwise
// effects: allocates memory (caller must free)
zint *strtozi(const char *str);

// strtozr(str) tries to convert str to a non-NULL zrep *
// returns the converted value if successful, returns NULL otherwise
// effects: allocates memory (caller must call z_clear)
zrep *strtozr(const char *str);

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
