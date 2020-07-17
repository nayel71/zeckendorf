#include "../include/types.h"

// add_len(s1, s2, len1, len2, len) returns a char array representing the sum of Zeckendorf representations
// given by s1 and s2, and stores its length at rlen if rlen != NULL
// requires: s1 and s2 represent Zeckendorf representations of lengths len1 and len2 respectively
// effects: allocates memory (caller must free), updates *rlen if rlen != NULL
char *add_len(const char *s1, const char *s2, size_t len1, size_t len2, size_t *rlen);
