#ifndef ZECKENDORF_H
#define ZECKENDORF_H

#include <stdbool.h>

// constants:
extern const long long LIMIT;
extern const char ZERO;
extern const char ONE;

typedef enum {INT, REP} ztype;
typedef struct zint zint;
typedef struct zrep zrep;

// definitions:
// - a zint * is a return value of strtoz(INT, s)
// - a zrep * is a return value of strtoz(REP, s)

// informally,
// - a zint represents a positive integer <= LIMIT
// - a zrep represents a string of ZEROs and ONEs starting with ONE,
//   that does not contain consecutive ONEs

// strtoz(typ, s) tries to convert s to a non-NULL zint * or zrep  *
// returns the converted value if successful, returns NULL otherwise
// effects: allocates memory (caller must call z_clear)
void *strtoz(ztype typ, const char *s);

// zrtostr(z) converts z to a string
// requires: z is non-NULL
// effects: allocates memory (caller must free)
char *zrtostr(const zrep *z);

// z_rep(n) returns the Zeckendorf representation of n
// requires: n is non-NULL
// effects: allocates memory (caller must call z_clear)
zrep *z_rep(const zint *n);

// z_clear(typ, ptr) frees all memory associated with ptr
// requires: ptr is non-NULL
// effects: memory associated with ptr is invalid
void z_clear(ztype typ, void *ptr);

// z_error(typ, param) prints an error message regarding param based
// on typ to stderr and returns EXIT_FAILURE
// effects: prints output
int z_error(ztype typ, const char *param);

#endif /* ZECKENDORF_H */
