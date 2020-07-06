#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <stdbool.h>
#include "zeckendorf.h" // zint, zrep, zint_is_valid, zrep_is_valid

// z_add(z1, z2) returns the sum of z1 and z2
// requires: zrep_is_valid(z1) && zrep_is_valid(z2)
// effects: allocates memory (caller must free)
zrep z_add(const zrep z1, const zrep z2);

// z_mul(z1, z2) returns the product of z1 and z2
// requires: zrep_is_valid(z1) && zrep_is_valid(z2)
// effects: allocates memory (caller must free)
zrep z_mul(const zrep z1, const zrep z2);

#endif /* ARITHMETIC_H */
