#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// digit constants:
extern const char zero;
extern const char one;
extern const char two;
extern const char three;
extern const int LIMIT;

// all of the following require: 
// 	- n is a positive integer <= LIMIT
// 	- a Zeckendorf representation is a binary string that starts with 1
// 	and contains no consecutive 1s

// zeckendorf(n) returns the Zeckendorf representation of n
// effects: allocates memory (caller must free)
char *zeckendorf(const int n);

// zecksqr(n) returns true if the Zeckendorf representation of n is a square
bool zecksqr(const int n);

// zeckpal(n) returns true if the Zeckendorf representation of n is a palindrome
bool zeckpal(const int n);

// zeck_add(str1, str2) returns the sum of the Zeckendorf representations str1 and str2
// effects: allocates memory (caller must free)
// requires: str1, str2 are Zeckendorf representations
char *zeck_add(const char *str1, const char *str2);

// zeck_mult(str1, str2) returns the product of the Zeckendorf representations str1 and str2
// effects: allocates memory (caller must free)
// requires: str1, str2 are Zeckendorf representations
char *zeck_mult(const char *str1, const char *str2);
