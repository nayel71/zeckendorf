#include "../include/arithmetic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// prints a list of commands and returns EXIT_FAILURE
static int help(const char *progname) {
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "%s n computes the Zeckendorf representation of n\n", progname);
	fprintf(stderr, "%s pow n computes the largest k such that the Zeckendorf representation of n is a k-power\n", progname);
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
		zint n = strtozi(command);
		ans = z_rep(n);
	} else if (strcmp(command, "pow") == 0 && argc == 3) {
		zint n = strtozi(argv[2]);
		printf("%d\n", z_pow(n));
	} else if (strcmp(command, "pal") == 0 && argc == 3) {
		zint n = strtozi(argv[2]);
		if (z_pal(n)) {
			puts("True");
		} else {
			puts("False");
		}
	} else if (strcmp(command, "add") == 0 && argc > 3) {
		ans = strtozr(argv[2]);
		for (int i = 3; i < argc; i++) {
			ans = z_add(ans, strtozr(argv[i]));
		}
	} else if (strcmp(command, "mul") == 0 && argc > 3) {
		ans = strtozr(argv[2]);
		for (int i = 3; i < argc; i++) {
			ans = z_mul(ans, strtozr(argv[i]));
		}
	} else {
		return help(argv[0]);
	}

	if (ans) {
		z_print(ans);
	}

	free(ans);
}
