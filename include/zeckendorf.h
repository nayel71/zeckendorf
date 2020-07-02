#ifndef ZECKENDORF_H
#define ZECKENDORF_H

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef long long z_int;
typedef char *z_rep;

// constants:
extern const char ZERO;
extern const char ONE;
extern const z_int LIMIT;

// all of the following require: 
// - n is a positive integer <= LIMIT
// - a Zeckendorf representation is a binary string consisting of ZEROs and ONEs,
//   that starts with ONE and does not contain consecutive ONEs

// zeckendorf(n) returns the Zeckendorf representation of n
// effects: allocates memory (caller must free)
char *zeckendorf(const z_int n);

// z_pow(n) returns the largest k such that zeckendorf(n) is a k-power
// i.e. of the form xx...xx (k repeated blocks) for some string x
int z_pow(const z_int n);

// z_pal(n) returns true if zeckendorf(n) is a palindrome, and false otherwise
bool z_pal(const z_int n);

// z_add(str1, str2) returns the sum of str1 and str2
// effects: allocates memory (caller must free)
// requires: str1, str2 are Zeckendorf representations
char *z_add(const char *str1, const char *str2);

// z_mul(str1, str2) returns the product of str1 and str2
// effects: allocates memory (caller must free)
// requires: str1, str2 are Zeckendorf representations
char *z_mul(const char *str1, const char *str2);

#endif /* ZECKENDORF_H */
