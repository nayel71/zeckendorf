#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "zeckendorf.h"

// z_add(z1, z2) returns the sum of z1 and z2
// requires: z1 and z2 are non-NULL
// effects: allocates memory (caller must call z_clear(REP, ... ))
zrep *z_add(const zrep *z1, const zrep *z2);

// z_mul(z1, z2) returns the product of z1 and z2
// requires: z1 and z2 are non-NULL
// effects: allocates memory (caller must call z_clear(REP, ... ))
zrep *z_mul(const zrep *z1, const zrep *z2);

#endif /* ARITHMETIC_H */
