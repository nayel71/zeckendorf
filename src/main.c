#include "../include/arithmetic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {BOUND, REP} zerror_t;

// returns an error message based on the error type
static const char *message(zerror_t err) {
	switch (err) {
		case BOUND: return "out-of-range argument";
		case REP:   return "invalid Zeckendorf representation";
	}
}

// prints an error message to stderr and returns EXIT_FAILURE
static int z_error(zerror_t err, const char *param) {
	fprintf(stderr, "Zeckendorf Error: %s %s\n", message(err), param);
	return EXIT_FAILURE;
}

// prints a list of commands to stderr and returns EXIT_FAILURE
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
		zint n = strtozi(argv[1]);
		if (zint_is_valid(n)) {
			ans = z_rep(n);
		} else {
			return z_error(BOUND, argv[1]);
		}
	} else if (strcmp(command, "pow") == 0 && argc == 3) {
		zint n = strtozi(argv[2]);
		if (zint_is_valid(n)) {
			printf("%d\n", z_pow(n));
		} else {
			return z_error(BOUND, argv[2]);
		}
	} else if (strcmp(command, "pal") == 0 && argc == 3) {
		zint n = strtozi(argv[2]);
		if (zint_is_valid(n) && z_pal(n)) {
			puts("True");
		} else if (zint_is_valid(n)) {
			puts("False");
		} else {
			return z_error(BOUND, argv[2]);
		}
	} else if (strcmp(command, "add") == 0 && argc > 3) {
		zrep z1 = strtozr(argv[2]);
		zrep z2 = strtozr(argv[3]);
		ans = z_add(z1, z2);
		if (ans) {
			for (int i = 4; i < argc; i++) {
				z1 = strtozr(argv[i]);
				z2 = z_add(ans, z1);
				if (z2) {
					int len = z_length(z2);
					ans = realloc(ans, (len + 1) * sizeof(zdigit));
					memcpy(ans, z2, (len + 1) * sizeof(zdigit));
					free(z2);
				} else {
					free(ans);
					return z_error(REP, argv[i]);
				}
			}
		} else if (!zrep_is_valid(z1)) {
			return z_error(REP, argv[2]);
		} else {
			return z_error(REP, argv[3]);
		}
	} else if (strcmp(command, "mul") == 0 && argc > 3) {
		zrep z1 = strtozr(argv[2]);
		zrep z2 = strtozr(argv[3]);
		ans = z_mul(z1, z2);
		if (ans) {
			for (int i = 4; i < argc; i++) {
				z1 = strtozr(argv[i]);
				z2 = z_mul(ans, z1);
				if (z2) {
					int len = z_length(z2);
					ans = realloc(ans, (len + 1) * sizeof(zdigit));
					memcpy(ans, z2, (len + 1) * sizeof(zdigit));
					free(z2);
				} else {
					free(ans);
					return z_error(REP, argv[i]);
				}
			}
		} else if (!zrep_is_valid(z1)) {
			return z_error(REP, argv[2]);
		} else {
			return z_error(REP, argv[3]);
		}
	} else {
		return help(argv[0]);
	}
	
	if (ans) {
		z_print(ans);
		free(ans);
	}
}
