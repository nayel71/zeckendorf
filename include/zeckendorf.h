#ifndef ZECKENDORF_H
#define ZECKENDORF_H

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// constants:
extern const char ZERO;
extern const char ONE;
extern const int LIMIT;

// all of the following require: 
// 	- n is a positive integer <= LIMIT
// 	- a Zeckendorf representation is a binary string consisting of ZEROs and ONEs,
//	that starts with ONE and does not contain consecutive ONEs

// zeckendorf(n) returns the Zeckendorf representation of n
// effects: allocates memory (caller must free)
char *zeckendorf(const int n);

// is_sqr(n) returns true if the Zeckendorf representation of n is a square
// (i.e. of the form xx, for some string x)
bool is_sqr(const int n);

// is_pal(n) returns true if the Zeckendorf representation of n is a palindrome
bool is_pal(const int n);

// add(str1, str2) returns the sum of the Zeckendorf representations str1 and str2
// effects: allocates memory (caller must free)
// requires: str1, str2 are Zeckendorf representations
char *add(const char *str1, const char *str2);

// mult(str1, str2) returns the product of the Zeckendorf representations str1 and str2
// effects: allocates memory (caller must free)
// requires: str1, str2 are Zeckendorf representations
char *mult(const char *str1, const char *str2);

#endif /* ZECKEONDORF_H */
