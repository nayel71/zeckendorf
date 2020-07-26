# Zeckendorf

Every positive integer has a unique representation as a sum of non-consecutive Fibonacci numbers, known as its [Zeckendorf representation](https://oeis.org/wiki/Zeckendorf_representation).

## API

```C
// zeckendorf.h

// constants:
extern const long long LIMIT;
extern const char ZERO;
extern const char ONE;

typedef enum {INT, REP} ztype;
typedef struct zint zint;
typedef struct zrep zrep;

// definitions:
// - a zint * is a return value of strtoz(INT, s)
// - a zrep * is a return value of strtoz(REP, s)

// informally,
// - a zint represents a positive integer <= LIMIT
// - a zrep represents a string of ZEROs and ONEs starting with ONE,
//   that does not contain consecutive ONEs

// strtoz(typ, s) tries to convert s to a non-NULL zint * or zrep  *
// returns the converted value if successful, returns NULL otherwise
// effects: allocates memory (caller must call z_clear(typ, ... ))
void *strtoz(ztype typ, const char *s);

// zrtostr(z) converts z to a string
// requires: z is non-NULL
// effects: allocates memory (caller must free)
char *zrtostr(const zrep *z);

// z_rep(n) returns the Zeckendorf representation of n
// requires: n is non-NULL
// effects: allocates memory (caller must call z_clear(REP, ... ))
zrep *z_rep(const zint *n);

// z_clear(typ, ptr) frees all memory associated with ptr
// requires: ptr is non-NULL
// effects: memory associated with ptr is invalid
void z_clear(ztype typ, void *ptr);

// z_error(typ, param) prints an error message regarding param based
// on typ to stderr and returns EXIT_FAILURE
// effects: prints output
int z_error(ztype typ, const char *param);

// arithmetic.h

// z_add(z1, z2) returns the sum of z1 and z2
// requires: z1 and z2 are non-NULL
// effects: allocates memory (caller must call z_clear)
zrep *z_add(const zrep *z1, const zrep *z2);

// z_mul(z1, z2) returns the product of z1 and z2
// requires: z1 and z2 are non-NULL
// effects: allocates memory (caller must call z_clear)
zrep *z_mul(const zrep *z1, const zrep *z2);
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
./zeckendorf add a b ... computes the sum of the Zeckendorf representations a, b, ...
./zeckendorf mul a b ... computes the product of the Zeckendorf representations a, b, ...
```

## Example

```
$ ./zeckendorf 10
10010
$ ./zeckendorf 11111111111111111111111
Zeckendorf Error: invalid argument 11111111111111111111111
$ ./zeckendorf add 10010 10100 10110
Zeckendorf Error: invalid Zeckendorf representation 10110
$ ./zeckendorf mul 10010 10100 10101
100101000010100
```

## Algorithm

See [the paper](AhlbachUsatineFrougnyPippenger.pdf).
