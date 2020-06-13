#include <stdio.h>
#include "../include/zeckendorf.h"

const int LIMIT = 2144908972;

// prints an error message and terminates the program
static void error(const char *msg, const char *param) {
	fprintf(stderr, "Error: %s %s\n", msg, param);
	exit(EXIT_FAILURE);
}

// prints a list of commands and terminates the program
static void help(const char *progname) {
	fprintf(stderr, "Usage: (see zeckendorf.h for details)\n");
	fprintf(stderr, "%s n            computes the Zeckendorf representation of n\n", progname);
	fprintf(stderr, "%s sqr? n       checks if the Zeckendorf representation of n is a square\n", progname);
	fprintf(stderr, "%s pal? n       checks if the Zeckendorf representation of n is a palindrome\n", progname);
	fprintf(stderr, "%s add a b ...  computes the sum of the Zeckendorf representations a, b, ...\n", progname);
	fprintf(stderr, "%s mult a b ... computes the product of the Zeckendorf representations a, b, ...\n", progname);
	exit(EXIT_FAILURE);
}

// checks if z is a valid Zeckendorf representation (see zeckendorf.h for details)
static bool is_valid(const char *z) {
	if (z[0] != ONE) return false;
	for (int index = strlen(z) - 1; index > 0; index--) {
		if (z[index] < ZERO || z[index] > ONE || z[index] - ZERO + z[index-1] - ZERO > 1) return false;
	}
	return true;
}

int main(int argc, char **argv) {
	if (argc < 2) help(argv[0]);
	char *command = argv[1], *ans = NULL;
	int n = atoi(command);

	if (n != 0) {
		if (argc != 2) help(argv[0]);
		if (n < 1 || n > LIMIT) error("out-of-range input", command);
		ans = zeckendorf(n);
	} else if (strcmp(command, "sqr?") == 0) {
		if (argc != 3) help(argv[0]);
		n = atoi(argv[2]);
		if (n < 1 || n > LIMIT) error("out-of-range input", argv[2]);
		if (is_sqr(n)) puts("True");
		else puts("False");
	} else if (strcmp(command, "pal?") == 0) {
		if (argc != 3) help(argv[0]);
		n = atoi(argv[2]);
		if (n < 1 || n > LIMIT) error("out-of-range input", argv[2]);
		if (is_pal(n)) puts("True");
		else puts("False");
	} else if (strcmp(command, "add") == 0) {
		if (argc < 4) help(argv[0]);
		if (!is_valid(argv[2])) error("invalid Zeckendorf representation", argv[2]);
		ans = argv[2];
		for (int i = 3; i < argc; i++) {
			if (!is_valid(argv[i])) error("invalid Zeckendorf representation", argv[i]);
			ans = add(ans, argv[i]);
		}
	} else if (strcmp(command, "mult") == 0) {
		if (argc < 4) help(argv[0]);
		if (!is_valid(argv[2])) error("invalid Zeckendorf representation", argv[2]);
		ans = argv[2];
		for (int i = 3; i < argc; i++) {
			if (!is_valid(argv[i])) error("invalid Zeckendorf representation", argv[i]);
			ans = mult(ans, argv[i]);
		}
	} else {
		help(argv[0]);
	}

	if (ans) {
		puts(ans);
		free(ans);
	}
}
