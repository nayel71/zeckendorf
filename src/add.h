#include "../include/types.h"

// add_len(s1, s2, len1, len2, len) returns a char array representing the sum of Zeckendorf representations
// given by s1 and s2, and stores its length at rlen
// requires: s1 and s2 represent Zeckendorf representations of lengths len1 and len2 respectively, rlen != NULL
// effects: allocates memory (caller must free), updates *rlen
char *add_len(const char *s1, const char *s2, const int len1, const int len2, int *rlen);
