#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <stdbool.h>
#include "zeckendorf.h" // zint, zrep, zint_is_valid, zrep_is_valid

// zeckendorf(n) returns the Zeckendorf representation of n
// requires: zint_is_valid(n) 
// effects: allocates memory (caller must free)
zrep zeckendorf(const zint n);

// z_pow(n) returns the largest integer k such that zeckendorf(n) is a k-power
// i.e. of the form xx...xx (k repeated blocks) for some string x
// requires: zint_is_valid(n) 
int z_pow(const zint n);

// z_pal(n) returns true if zeckendorf(n) is a palindrome, and false otherwise
// requires: zint_is_valid(n) 
bool z_pal(const zint n);

// z_add(z1, z2) returns the sum of z1 and z2
// requires: zrep_is_valid(z1) && zrep_is_valid(z2)
// effects: allocates memory (caller must free)
zrep z_add(const zrep z1, const zrep z2);

// z_mul(z1, z2) returns the product of z1 and z2
// requires: zrep_is_valid(z1) && zrep_is_valid(z2)
// effects: allocates memory (caller must free)
zrep z_mul(const zrep z1, const zrep z2);

#endif /* ARITHMETIC_H */
