# A Program for Zeckendorf Arithmetic

Every positive integer has a unique representation as a sum of non-consecutive Fibonacci numbers, known as its [Zeckendorf representation](https://oeis.org/wiki/Zeckendorf_representation). This program can be used for the following purposes.

- Compute the Zeckendorf representation of `n`.
- Check if the Zeckendorf representation of `n` is a square/palindrome.
- Compute the sum/product of an arbitrary number of Zeckendorf representations.

See `zeckendorf.h` and the paper by Frougny et al. for details.

## Installation

- `git clone https://github.com/nayel71/zeckendorf.git`
- `cd zeckendorf`
- `make`

## Usage

Upon successful installation, running `./zeckendorf` should print the following output.

```
Usage: (see zeckendorf.h for details)
./zeckendorf n            computes the Zeckendorf representation of n
./zeckendorf sqr? n       checks if the Zeckendorf representation of n is a square
./zeckendorf pal? n       checks if the Zeckendorf representation of n is a palindrome
./zeckendorf add a b ...  computes the sum of the Zeckendorf representations a, b, ...
./zeckendorf mult a b ... computes the product of the Zeckendorf representations a, b, ...
```
