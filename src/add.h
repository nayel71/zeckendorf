#include "../include/zeckendorf.h"

// add_len(z1, z2, len1, len2, len) returns the sum of z1 and z2 and stores its length at len
// requires: z1 and z2 are Zeckendorf representations of lengths len1 and len2 respectively
// effects: allocates memory (caller must free), updates len
zrep add_len(const zrep z1, const zrep z2, const int len1, const int len2, int *len);
