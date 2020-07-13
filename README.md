# Zeckendorf

Every positive integer has a unique representation as a sum of non-consecutive Fibonacci numbers, known as its [Zeckendorf representation](https://oeis.org/wiki/Zeckendorf_representation).

## API

```C
// zeckendorf.h

// definitions:
// - a zint is either zero or a non-zero return value of strtozi
// - a zrep is either NULL or a non-NULL return value of strtozr

// informally, (see types.h)
// - a zint is a non-negative integer <= LIMIT
// - a zrep is a binary string consisting of ZEROs and ONEs,
//   that starts with ONE and does not contain consecutive ONEs

// strtozi(str) tries to convert str to a non-zero zint
// returns the converted value if successful, returns zero otherwise
zint strtozi(const char *str);

// strtozr(str) tries to convert str to a non-NULL zrep
// returns the converted value if successful, returns NULL otherwise
// effects: allocates memory (caller must z_clear the return address)
zrep strtozr(const char *str);

// z_rep(n) returns the Zeckendorf representation of n
// requires: n is non-zero
// effects: allocates memory (caller must z_clear the return address)
zrep z_rep(const zint n);

// z_length(z) returns the length of z
// requires: z is non-NULL
int z_length(const zrep z);

// z_print(z) prints z to stdout 
// requires: z is non-NULL
// effects: prints output
void z_print(const zrep z);

// z_copy(z1, z2) copies z1 to z2
// requires: z1 and z2 are non-NULL
// effects: allocates memory (caller must z_clear(z2))
void z_copy(const zrep z1, zrep *z2);

// z_clear(z) frees the memory at z
void z_clear(zrep *z);

// z_pow(n) returns the largest integer k such that z_rep(n) is a k-power
// i.e. of the form xx...xx (k repeated blocks) for some string x
// requires: n is non-zero
int z_pow(const zint n);

// z_pal(n) returns true if z_rep(n) is a palindrome, returns false otherwise
// requires: n is non-zero 
bool z_pal(const zint n);

// arithmetic.h

// z_add(z1, z2) returns the sum of z1 and z2
// requires: z1 and z1 are non-NULL
// effects: allocates memory (caller must z_clear the return address)
zrep z_add(const zrep z1, const zrep z2);

// z_mul(z1, z2) returns the product of z1 and z2
// requires: z1 and z1 are non-NULL
// effects: allocates memory (caller must z_clear the return address)
zrep z_mul(const zrep z1, const zrep z2);

// error.h

// z_error(err, param) prints an error message regarding param based on
// err to stderr and returns EXIT_FAILURE
int z_error(zerror_t err, const char *param);
```

## Installation

- `git clone https://github.com/nayel71/zeckendorf.git`
- `cd zeckendorf`
- `make`

## Usage

Upon successful installation, running `./zeckendorf` should print the following output.

```
Usage:
./zeckendorf n computes the Zeckendorf representation of n
./zeckendorf pow n computes the largest integer k such that the Zeckendorf representation of n is a k-power
./zeckendorf pal n checks if the Zeckendorf representation of n is a palindrome
./zeckendorf add a b ... computes the sum of the Zeckendorf representations a, b, ...
./zeckendorf mul a b ... computes the product of the Zeckendorf representations a, b, ...
```

## Example

```
$ ./zeckendorf 10
10010
$ ./zeckendorf 11111111111111111111111
Zeckendorf Error: out-of-range argument 11111111111111111111111
$ ./zeckendorf pow 54
4
$ ./zeckendorf pal 1022
True
$ ./zeckendorf add 10010 10100 10110
Zeckendorf Error: invalid Zeckendorf representation 10110
$ ./zeckendorf mul 10010 10100 10101
100101000010100
```

## Algorithm

See [the paper](AhlbachUsatineFrougnyPippenger.pdf).
