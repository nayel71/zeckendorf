#ifndef ZECKENDORF_H
#define ZECKENDORF_H

#include "types.h"
#include <stdbool.h>

// constants:
extern const zint LIMIT;
extern const zdigit ZERO;
extern const zdigit ONE;

// definitions:
// - a zint is either zero or a non-zero return value of strtozi
// - a zrep is either NULL or a non-NULL return value of strtozr

// informally,
// - a zint is a non-negative integer <= LIMIT
// - a zrep is a binary string consisting of ZEROs and ONEs,
//   that starts with ONE and does not contain consecutive ONEs

// strtozi(str) tries to convert str to a non-zero zint
// returns the converted value if successful, returns zero otherwise
zint strtozi(const char *str);

// strtozr(str) tries to convert str to a non-NULL zrep
// returns the converted value if successful, returns NULL otherwise
// effects: allocates memory (caller must free)
zrep strtozr(const char *str);

// z_rep(n) returns the Zeckendorf representation of n
// requires: n is non-zero
// effects: allocates memory (caller must free)
zrep z_rep(const zint n);

// z_length(z) returns the length of z
// requires: z is non-NULL
int z_length(const zrep z);

// z_print(z) prints z to stdout 
// requires: z is non-NULL
// effects: may print to stdout
void z_print(const zrep z);

// z_pow(n) returns the largest integer k such that z_rep(n) is a k-power
// i.e. of the form xx...xx (k repeated blocks) for some string x
// requires: n is non-zero
int z_pow(const zint n);

// z_pal(n) returns true if z_rep(n) is a palindrome, and false otherwise
// requires: n is non-zero 
bool z_pal(const zint n);

#endif /* ZECKENDORF_H */
