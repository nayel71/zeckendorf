#ifndef ZECKENDORF_H
#define ZECKENDORF_H

// constants:
extern const long long LIMIT;
extern const char ZERO;
extern const char ONE;

typedef enum {ZINT, ZREP} ztype;
typedef struct zint zint;
typedef struct zrep zrep;

// definitions:
// - a zint * is a return value of z_strto(ZINT, ... )
// - a zrep * is a return value of z_strto(ZREP, ... )

// informally,
// - a zint represents a positive integer <= LIMIT
// - a zrep represents a string of ZEROs and ONEs starting with ONE,
//   that does not contain consecutive ONEs

// z_strto(typ, s) tries to convert s to a non-NULL zint * or zrep *
// returns the converted value if successful, returns NULL otherwise
// effects: allocates memory (caller must call z_clear(typ, ... ))
void *z_strto(ztype typ, const char *s);

// z_tostr(z) converts z to a string
// requires: z is non-NULL
// effects: allocates memory (caller must free)
char *z_tostr(const zrep *z);

// z_rep(n) returns the Zeckendorf representation of n
// requires: n is non-NULL
// effects: allocates memory (caller must call z_clear(ZREP, ... ))
zrep *z_rep(const zint *n);

// z_clear(typ, ptr) frees all memory associated with ptr
// requires: ptr is a non-NULL zint * or zrep * corresponding to typ
// effects: memory associated with ptr is invalid
void z_clear(ztype typ, void *ptr);

// z_error(typ, param) prints an error message regarding param based
// on typ to stderr and returns EXIT_FAILURE
// effects: prints output
int z_error(ztype typ, const char *param);

#endif /* ZECKENDORF_H */
