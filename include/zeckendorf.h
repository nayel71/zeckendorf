#ifndef ZECKENDORF_H
#define ZECKENDORF_H

#include "types.h"
#include <stdbool.h>

// definitions:
// - a zint is either zero or a non-zero return value of strtozi
// - a zrep is either NULL or a non-NULL return value of strtozr

// informally, (see types.h)
// - a zint is a non-negative integer <= LIMIT
// - a zrep is a binary string consisting of ZEROs and ONEs,
//   that starts with ONE and does not contain consecutive ONEs

// strtozi(str) tries to convert str to a non-zero zint
// returns the converted value if successful, returns zero otherwise
zint strtozi(const char *str);

// strtozr(str) tries to convert str to a non-NULL zrep
// returns the converted value if successful, returns NULL otherwise
// effects: allocates memory (caller must z_clear the return address)
zrep strtozr(const char *str);

// z_rep(n) returns the Zeckendorf representation of n
// requires: n is non-zero
// effects: allocates memory (caller must z_clear the return address)
zrep z_rep(const zint n);

// z_length(z) returns the length of z
// requires: z is non-NULL
int z_length(const zrep z);

// z_print(z) prints z to stdout 
// requires: z is non-NULL
// effects: prints output
void z_print(const zrep z);

// z_copy(z1, z2) copies z1 to z2
// requires: z1 and z2 are non-NULL
// effects: allocates memory (caller must z_clear(z2))
void z_copy(const zrep z1, zrep *z2);

// z_clear(z) frees the memory at z
void z_clear(zrep *z);

// z_pow(n) returns the largest integer k such that z_rep(n) is a k-power
// i.e. of the form xx...xx (k repeated blocks) for some string x
// requires: n is non-zero
int z_pow(const zint n);

// z_pal(n) returns true if z_rep(n) is a palindrome, returns false otherwise
// requires: n is non-zero 
bool z_pal(const zint n);

#endif /* ZECKENDORF_H */
