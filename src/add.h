#include "../include/types.h"

// add_len(s1, s2, len1, len2, len) returns the string representation of the sum of the
// Zeckendorf representations given by s1 and s2, and stores its length at rlen if rlen != NULL
// requires: strlen(s1) == len1 && strlen(s2) == len2
// effects: allocates memory (caller must free), updates *rlen if len != NULL
char *add_len(const char *s1, const char *s2, const int len1, const int len2, int *rlen);
