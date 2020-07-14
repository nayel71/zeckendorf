#include "../include/types.h"

// add_len(z1, z2, len1, len2, len) returns the sum of z1 and z2 and stores its length at rlen if rlen != NULL
// requires: z_length(z1) == len1 && z_length(z2) == len2
// effects: allocates memory (caller must z_clear the return address), updates *rlen if len != NULL
zrep add_len(const zrep z1, const zrep z2, const int len1, const int len2, int *rlen);
