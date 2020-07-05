#ifndef ZECKENDORF_H
#define ZECKENDORF_H

#include <stdbool.h>
#include "types.h" // z_int, z_rep, z_int_is_valid, z_rep_is_valid

// zeckendorf(n) returns the Zeckendorf representation of n
// requires: z_int_is_valid(n) 
// effects: allocates memory (caller must free)
z_rep zeckendorf(const z_int n);

// z_pow(n) returns the largest integer k such that zeckendorf(n) is a k-power
// i.e. of the form xx...xx (k repeated blocks) for some string x
// requires: z_int_is_valid(n) 
int z_pow(const z_int n);

// z_pal(n) returns true if zeckendorf(n) is a palindrome, and false otherwise
// requires: z_int_is_valid(n) 
bool z_pal(const z_int n);

// z_add(str1, str2) returns the sum of str1 and str2
// requires: z_rep_is_valid(str1) && z_rep_is_valid(str2)
// effects: allocates memory (caller must free)
z_rep z_add(const z_rep str1, const z_rep str2);

// z_mul(str1, str2) returns the product of str1 and str2
// requires: z_rep_is_valid(str1) && z_rep_is_valid(str2)
// effects: allocates memory (caller must free)
z_rep z_mul(const z_rep str1, const z_rep str2);

#endif /* ZECKENDORF_H */
