#ifndef ZREP_H
#define ZREP_H

#include <zeckendorf.h>
#include <stddef.h>

// zrep_new(arr, len) allocates memory for a new zrep * representing arr
// requires: arr is allocated and represents a valid zrep of length len
// effects: allocates memory (caller must call z_clear(REP, ... ))
zrep *zrep_new(char *arr, size_t len);

// zrep_arr(z) returns the array associated with z
// requires: z is non-NULL
char *zrep_arr(const zrep *z);

// zrep_len(z) returns the length of z
// requires: z is non-NULL
size_t zrep_len(const zrep *z);

// zrep_free(z) frees all memory associated with z
// requires: z is non-NULL
// effects: memory associated with z is invalid
void zrep_free(zrep *z);

#endif /* ZREP_H */
