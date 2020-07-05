# Zeckendorf Arithmetic

Every positive integer has a unique representation as a sum of non-consecutive Fibonacci numbers, known as its [Zeckendorf representation](https://oeis.org/wiki/Zeckendorf_representation). This program can be used for the following purposes.

- Compute the Zeckendorf representation of `n`.
- Check if the Zeckendorf representation of `n` is a power/palindrome.
- Compute the sum/product of an arbitrary number of Zeckendorf representations.

See `zeckendorf.h` and the paper by Frougny et al. for details.

## Installation

- `git clone https://github.com/nayel71/zeckendorf.git`
- `cd zeckendorf`
- `make`

## Usage

Upon successful installation, running `./zeckendorf` should print the following output.

```
Usage:
./zeckendorf n computes the Zeckendorf representation of n
./zeckendorf pow n computes the largest k such that the Zeckendorf representation of n is a k-power
./zeckendorf pal n checks if the Zeckendorf representation of n is a palindrome
./zeckendorf add a b ... computes the sum of the Zeckendorf representations a, b, ...
./zeckendorf mul a b ... computes the product of the Zeckendorf representations a, b, ...
```

## API

`zeckendorf.h` contains the public API below. To use the API in your project, `#include "../include/zeckendorf.h"` and replace `main.c` with your source file(s).

```C
#include <stdbool.h>
#include "types.h" // z_int, z_rep, z_int_is_valid, z_rep_is_valid

// zeckendorf(n) returns the Zeckendorf representation of n
// requires: z_int_is_valid(n) 
// effects: allocates memory (caller must free)
z_rep zeckendorf(const z_int n);

// z_pow(n) returns the largest integer k such that zeckendorf(n) is a k-power
// i.e. of the form xx...xx (k repeated blocks) for some string x
// requires: z_int_is_valid(n) 
int z_pow(const z_int n);

// z_pal(n) returns true if zeckendorf(n) is a palindrome, and false otherwise
// requires: z_int_is_valid(n) 
bool z_pal(const z_int n);

// z_add(str1, str2) returns the sum of str1 and str2
// requires: z_rep_is_valid(str1) && z_rep_is_valid(str2)
// effects: allocates memory (caller must free)
z_rep z_add(const z_rep str1, const z_rep str2);

// z_mul(str1, str2) returns the product of str1 and str2
// requires: z_rep_is_valid(str1) && z_rep_is_valid(str2)
// effects: allocates memory (caller must free)
z_rep z_mul(const z_rep str1, const z_rep str2);

```
