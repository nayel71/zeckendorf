#include <stdio.h>
#include "zeckendorf.h"

const int LIMIT = 2144908972;

// prints an error message and terminates the program
static void error(const char *msg, const char *param) {
	fprintf(stderr, "Error: %s %s\n", msg, param);
	exit(EXIT_FAILURE);
}

// prints a list of commands
static void print_help(const char *progname) {
	fprintf(stderr, "Usage: (see zeckendorf.h for details)\n");
	fprintf(stderr, "%s n            computes the Zeckendorf representation of n\n", progname);
	fprintf(stderr, "%s sqr? n       checks if the Zeckendorf representation of n is a square\n", progname);
	fprintf(stderr, "%s pal? n       checks if the Zeckendorf representation of n is a palindrome\n", progname);
	fprintf(stderr, "%s add a b ...  computes the sum of the Zeckendorf representations a, b, ...\n", progname);
	fprintf(stderr, "%s mult a b ... computes the product of the Zeckendorf representations a, b, ...\n", progname);
	exit(EXIT_FAILURE);
}

// checks if z is a valid Zeckendorf representation (see zeckendorf.h for details)
static bool is_zeck(const char *z) {
	if (z[0] != one) return false;
	for (int index = strlen(z) - 1; index > 0; index--) {
		if (z[index] < zero || z[index] > one || z[index] - zero + z[index-1] - zero > 1) return false;
	}
	return true;
}

int main(int argc, char **argv) {
	if (argc < 2) print_help(argv[0]);
	char *command = argv[1], *ans = NULL;
	int n = atoi(command);

	if (n != 0) {
		if (argc != 2) print_help(argv[0]);
		if (n < 1 || n > LIMIT) error("out-of-range input", command);
		ans = zeckendorf(n);
		puts(ans);
		free(ans);
	} else if (strcmp(command, "sqr?") == 0) {
		if (argc != 3) print_help(argv[0]);
		n = atoi(argv[2]);
		if (n < 1 || n > LIMIT) error("out-of-range input", argv[2]);
		if (zecksqr(n)) puts("True");
		else puts("False");
	} else if (strcmp(command, "pal?") == 0) {
		if (argc != 3) print_help(argv[0]);
		n = atoi(argv[2]);
		if (n < 1 || n > LIMIT) error("out-of-range input", argv[2]);
		if (zeckpal(n)) puts("True");
		else puts("False");
	} else if (strcmp(command, "add") == 0) {
		if (argc < 4) print_help(argv[0]);
		if (!is_zeck(argv[2])) error("invalid Zeckendorf representation", argv[2]);
		ans = argv[2];
		for (int i = 3; i < argc; i++) {
			if (!is_zeck(argv[i])) error("invalid Zeckendorf representation", argv[i]);
			ans = zeck_add(ans, argv[i]);
		}
		puts(ans);
		free(ans);
	} else if (strcmp(command, "mult") == 0) {
		if (argc < 4) print_help(argv[0]);
		if (!is_zeck(argv[2])) error("invalid Zeckendorf representation", argv[2]);
		ans = argv[2];
		for (int i = 3; i < argc; i++) {
			if (!is_zeck(argv[i])) error("invalid Zeckendorf representation", argv[i]);
			ans = zeck_mult(ans, argv[i]);
		}
		puts(ans);
		free(ans);
	} else {
		print_help(argv[0]);
	}
}
