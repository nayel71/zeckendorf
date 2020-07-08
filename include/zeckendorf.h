#ifndef ZECKENDORF_H
#define ZECKENDORF_H

#include "types.h"
#include <stdbool.h>

// constants:
extern const zint LIMIT;
extern const zdigit ZERO;
extern const zdigit ONE;

// definitions:
// (formal)
// - a zint is a non-zero return value of strtozi
// - a zrep is a non-NULL return value of strtozr
// (informal)
// - a zint is is a positive integer <= LIMIT
// - a zrep is a binary string consisting of ZEROs and ONEs,
//   that starts with ONE and does not contain consecutive ONEs

// strtozi(str) tries to convert str to a zint
// returns the converted value if successful, returns 0 otherwise
zint strtozi(const char *str);

// strtozr(str) tries to convert str to a zrep
// returns the converted value if successful, returns NULL otherwise
zrep strtozr(const char *str);

// zint_is_valid(n) returns true if n is a zint
// returns false otherwise
bool zint_is_valid(const zint n);

// zrep_is_valid(z) returns true if z is a zrep
// returns false otherwise
bool zrep_is_valid(const zrep z);

// z_rep(n) returns the Zeckendorf representation of n if zint_is_valid(n)
// returns NULL otherwise
// effects: allocates memory (caller must free) if return value is not NULL
zrep z_rep(const zint n);

// z_length(z) returns the length of z
// requires: zrep_is_valid(z)
int z_length(const zrep z);

// z_print(z) prints z to stdout 
// requires: zrep_is_valid(z)
// effects: may print to stdout
void z_print(const zrep z);

// z_pow(n) returns the largest integer k such that z_rep(n) is a k-power
// i.e. of the form xx...xx (k repeated blocks) for some string x
// requires: zint_is_valid(n)
int z_pow(const zint n);

// z_pal(n) returns true if z_rep(n) is a palindrome, and false otherwise
// requires: zint_is_valid(n) 
bool z_pal(const zint n);

#endif /* ZECKENDORF_H */
