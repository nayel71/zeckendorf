#include <stdio.h>
#include "../include/zeckendorf.h"

const z_int LIMIT = 9217463444206948444;

typedef enum {BOUND, REP} error_t;

// returns an error message based on the error type
static const char *message(error_t err) {
	switch (err) {
		case BOUND: return "out-of-range argument";
		case REP:   return "invalid Zeckendorf representation";
	}
}

// prints an error message and returns EXIT_FAILURE
static int error(error_t err, const char *param) {
	fprintf(stderr, "Error: %s %s\n", message(err), param);
	return EXIT_FAILURE;
}

// prints a list of commands and returns EXIT_FAILURE
static int help(const char *progname) {
	fprintf(stderr, "Usage: (see zeckendorf.h for details)\n");
	fprintf(stderr, "%s n computes the Zeckendorf representation of n\n", progname);
	fprintf(stderr, "%s pow n computes the largest k such that the Zeckendorf representation of n is a k-power\n", progname);
	fprintf(stderr, "%s pal n checks if the Zeckendorf representation of n is a palindrome\n", progname);
	fprintf(stderr, "%s add a b ... computes the sum of the Zeckendorf representations a, b, ...\n", progname);
	fprintf(stderr, "%s mul a b ... computes the product of the Zeckendorf representations a, b, ...\n", progname);
	return EXIT_FAILURE;
}

// checks if z is a valid Zeckendorf representation (see zeckendorf.h for details)
static bool is_valid(const char *z) {
	if (z[0] != ONE) return false;
	for (int index = strlen(z) - 1; index > 0; index--) {
		if (z[index] < ZERO || z[index] > ONE || z[index] - ZERO + z[index-1] - ZERO > 1) {
			return false;
		}
	}
	return true;
}

int main(int argc, char **argv) {
	if (argc < 2) {
		return help(argv[0]);
	}

	char *command = argv[1], *ans = NULL;
	z_int n = strtoll(command, NULL, 0);

	if (n != 0) {
		if (argc != 2) {
			return help(argv[0]);
		} else if (n < 1 || n > LIMIT) {
			return error(BOUND, command);
		} else {
			ans = zeckendorf(n);
		}
	} else if (strcmp(command, "pow") == 0) {
		if (argc != 3) {
			return help(argv[0]);
		}
		n = strtoll(argv[2], NULL, 0);
		if (n < 1 || n > LIMIT) {
			return error(BOUND, argv[2]);
		} else {
			printf("%d\n", z_pow(n));
		}
	} else if (strcmp(command, "pal") == 0) {
		if (argc != 3) {
			return help(argv[0]);
		}
		n = strtoll(argv[2], NULL, 0);
		if (n < 1 || n > LIMIT) {
			return error(BOUND, argv[2]);
		} else if (z_pal(n)) {
			puts("True");
		} else {
			puts("False");
		}
	} else if (strcmp(command, "add") == 0) {
		if (argc < 4) {
			return help(argv[0]);
		} else if (!is_valid(argv[2])) {
			return error(REP, argv[2]);
		} else {
			ans = argv[2];
			for (int i = 3; i < argc; i++) {
				if (!is_valid(argv[i])) {
					return error(REP, argv[i]);
				} else {
					ans = z_add(ans, argv[i]);
				}
			}
		}
	} else if (strcmp(command, "mul") == 0) {
		if (argc < 4) {
			return help(argv[0]);
		} else if (!is_valid(argv[2])) {
			return error(REP, argv[2]);
		} else {
			ans = argv[2];
			for (int i = 3; i < argc; i++) {
				if (!is_valid(argv[i])) {
					return error(REP, argv[i]);
				} else {
					ans = z_mul(ans, argv[i]);
				}
			}
		}
	} else {
		return help(argv[0]);
	}

	if (ans) {
		puts(ans);
		free(ans);
	}
}
