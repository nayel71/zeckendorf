# Zeckendorf

Every positive integer has a unique representation as a sum of non-consecutive Fibonacci numbers, known as its [Zeckendorf representation](https://oeis.org/wiki/Zeckendorf_representation).

## API

```C
// zeckendorf.h

// constants:
extern const zint LIMIT;
extern const zdigit ZERO;
extern const zdigit ONE;

// definitions:
// - a zint is either zero or a non-zero return value of strtozi
// - a zrep is either NULL or a non-NULL return value of strtozr
// informally,
// - a zint is a non-negative integer <= LIMIT
// - a zrep is a binary string consisting of ZEROs and ONEs,
//   that starts with ONE and does not contain consecutive ONEs

// strtozi(str) tries to convert str to a non-zero zint
// returns the converted value if successful, returns zero otherwise
zint strtozi(const char *str);

// strtozr(str) tries to convert str to a non-NULL zrep
// returns the converted value if successful, returns NULL otherwise
// effects: allocates memory (caller must free) if return value is not NULL
zrep strtozr(const char *str);

// zint_is_valid(n) returns true if n is a non-zero zint, returns false otherwise
bool zint_is_valid(const zint n);

// zrep_is_valid(z) returns true if z is a non-NULL zrep, returns false otherwise
bool zrep_is_valid(const zrep z);

// z_rep(n) returns the Zeckendorf representation of n if n is a non-zero zint
// returns NULL otherwise
// effects: allocates memory (caller must free) if return value is not NULL
zrep z_rep(const zint n);

// z_length(z) returns the length of z
// requires: zrep_is_valid(z)
int z_length(const zrep z);

// z_print(z) prints z to stdout 
// requires: zrep_is_valid(z)
// effects: may print to stdout
void z_print(const zrep z);

// z_pow(n) returns the largest integer k such that z_rep(n) is a k-power
// i.e. of the form xx...xx (k repeated blocks) for some string x
// requires: zint_is_valid(n)
int z_pow(const zint n);

// z_pal(n) returns true if z_rep(n) is a palindrome, and false otherwise
// requires: zint_is_valid(n) 
bool z_pal(const zint n);

// arithmetic.h

// z_add(z1, z2) returns the sum of z1 and z2 if zrep_is_valid(z1) && zrep_is_valid(z2)
// returns NULL otherwise
// effects: allocates memory (caller must free) if return value is not NULL
zrep z_add(const zrep z1, const zrep z2);

// z_mul(z1, z2) returns the product of z1 and z2 if zrep_is_valid(z1) && zrep_is_valid(z2)
// returns NULL otherwise
// effects: allocates memory (caller must free) if return value is not NULL
zrep z_mul(const zrep z1, const zrep z2);
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
./zeckendorf pow n computes the largest k such that the Zeckendorf representation of n is a k-power
./zeckendorf pal n checks if the Zeckendorf representation of n is a palindrome
./zeckendorf add a b ... computes the sum of the Zeckendorf representations a, b, ...
./zeckendorf mul a b ... computes the product of the Zeckendorf representations a, b, ...
```

## Algorithm

See [the paper](AhlbachUsatineFrougnyPippenger.pdf).
