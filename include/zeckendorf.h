#ifndef ZECKENDORF_H
#define ZECKENDORF_H

#include "types.h"
#include <stdbool.h>

typedef enum {BOUND, REP} error_t;

// constants:
extern const zint LIMIT;
extern const zdigit ZERO;
extern const zdigit ONE;

// z_rep(n) returns the Zeckendorf representation of n
// requires: zint_is_valid(n) 
// effects: allocates memory (caller must free)
zrep z_rep(const zint n);

// zrep_is_valid(z) returns true if z is a Zeckendorf representation, returns false otherwise
// (a Zeckendorf representation is a binary string consisting of ZEROs and ONEs,
// that starts with ONE and does not contain consecutive ONEs)
bool zrep_is_valid(const zrep z);

// zint_is_valid(n) returns true if n is a positive integer <= LIMIT, returns false otherwise
bool zint_is_valid(const zint n);

// strtozi(str) tries to convert str to a valid zint
// if successful, returns the converted value
// if unsuccessful, calls exit(z_error(BOUND, str)) (see below)
zint strtozi(const char *str);

// strtozr(str) tries to convert str to a valid zrep
// if successful, returns the converted value
// if unsuccessful, calls exit(z_error(REP, str)) (see below)
zrep strtozr(const char *str);

// z_length(z) returns the length of z
// requires: zrep_is_valid(z)
int z_length(const zrep z);

// z_print(z) prints z to stdout
// requires: zrep_is_valid(z)
// effects: prints output
void z_print(const zrep z);

// z_pow(n) returns the largest integer k such that z_rep(n) is a k-power
// i.e. of the form xx...xx (k repeated blocks) for some string x
// requires: zint_is_valid(n) 
int z_pow(const zint n);

// z_pal(n) returns true if z_rep(n) is a palindrome, and false otherwise
// requires: zint_is_valid(n) 
bool z_pal(const zint n);

// z_error(err, param) prints an error message regarding err and param to stderr
// and returns EXIT_FAILURE
int z_error(error_t err, const char *param);

#endif /* ZECKENDORF_H */
