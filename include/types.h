#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

typedef long long z_int;
typedef char z_digit;
typedef z_digit *z_rep;
typedef enum {BOUND, REP} error_t;

// constants:
extern const z_int LIMIT;
extern const z_digit ZERO;
extern const z_digit ONE;

// returns true if z is a Zeckendorf representation, and false otherwise
// (a Zeckendorf representation is a binary string consisting of ZEROs and ONEs,
// that starts with ONE and does not contain consecutive ONEs)
// effects: if the return value is true, also updates *len with the length of z
// additionally, if print == true, prints z to stdout
bool z_rep_is_valid(const z_rep z, int *len, bool print);

// returns true if 0 < n <= LIMIT, and false otherwise
bool z_int_is_valid(const z_int n);

// prints an error message to stderr and returns EXIT_FAILURE
int z_error(error_t err, const char *param);

// tries to convert str to a valid z_int; if unsuccessful, calls exit(z_error(BOUND, str))
z_int strtozi(const char *str);

// tries to convert str to a valid z_rep; if unsuccessful, calls exit(z_error(REP, str))
z_rep strtozr(const char *str);

#endif /* TYPES_H */
