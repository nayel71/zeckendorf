#include "../include/types.h"

// add_len(z1, z2, len1, len2, len) returns the sum of z1 and z2 and stores its length at len
// requires: z1 and z2 are Zeckendorf representations of lengths len1 and len2 respectively
// effects: allocates memory (caller must free), updates len
z_rep add_len(const z_rep z1, const z_rep z2, const int len1, const int len2, int *len);
