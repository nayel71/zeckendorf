#include "../include/arithmetic.h"
#include "../include/error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// prints a list of commands to stderr and returns EXIT_FAILURE
static int help(const char *progname) {
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "%s n computes the Zeckendorf representation of n\n", progname);
	fprintf(stderr, "%s pow n computes the largest integer k such that the Zeckendorf representation of n is a k-power\n", progname);
	fprintf(stderr, "%s pal n checks if the Zeckendorf representation of n is a palindrome\n", progname);
	fprintf(stderr, "%s add a b ... computes the sum of the Zeckendorf representations a, b, ...\n", progname);
	fprintf(stderr, "%s mul a b ... computes the product of the Zeckendorf representations a, b, ...\n", progname);
	return EXIT_FAILURE;
}

int main(int argc, char **argv) {
	if (argc < 2) {
		return help(argv[0]);
	}

	char *command = argv[1];
	zrep ans = NULL;

	if (argc == 2) {
		zint n = strtozi(argv[1]);
		if (n) {
			ans = z_rep(n);
		} else {
			return z_error(BOUND, argv[1]);
		}
	} else if (strcmp(command, "pow") == 0 && argc == 3) {
		zint n = strtozi(argv[2]);
		if (n) {
			printf("%d\n", z_pow(n));
		} else {
			return z_error(BOUND, argv[2]);
		}
	} else if (strcmp(command, "pal") == 0 && argc == 3) {
		zint n = strtozi(argv[2]);
		if (n && z_pal(n)) {
			puts("True");
		} else if (n) {
			puts("False");
		} else {
			return z_error(BOUND, argv[2]);
		}
	} else if (strcmp(command, "add") == 0 && argc > 3) {
		zrep z1 = strtozr(argv[2]);
		zrep z2 = strtozr(argv[3]);
		if (!z1) {
			z_clear(&z2);
			return z_error(REP, argv[2]);
		} else if (!z2) {
			z_clear(&z1);
			return z_error(REP, argv[3]);
		} else {
			ans = z_add(z1, z2);
			z_clear(&z1);
			z_clear(&z2);
			for (int i = 4; i < argc; i++) {
				z1 = strtozr(argv[i]);
				if (!z1) {
					z_clear(&ans);
					return z_error(REP, argv[i]);
				} else {
					z2 = z_add(ans, z1);
					z_clear(&z1);
					z_copy(z2, &ans);
					z_clear(&z2);
				}
			}
		}
	} else if (strcmp(command, "mul") == 0 && argc > 3) {
		zrep z1 = strtozr(argv[2]);
		zrep z2 = strtozr(argv[3]);
		if (!z1) {
			z_clear(&z2);
			return z_error(REP, argv[2]);
		} else if (!z2) {
			z_clear(&z1);
			return z_error(REP, argv[3]);
		} else {
			ans = z_mul(z1, z2);
			z_clear(&z1);
			z_clear(&z2);
			for (int i = 4; i < argc; i++) {
				z1 = strtozr(argv[i]);
				if (!z1) {
					z_clear(&ans);
					return z_error(REP, argv[i]);
				} else {
					z2 = z_mul(ans, z1);
					z_clear(&z1);
					z_copy(z2, &ans);
					z_clear(&z2);
				}
			}
		}
	} else {
		return help(argv[0]);
	}
	
	if (ans) {
		z_print(ans);
		z_clear(&ans);
	}
}
