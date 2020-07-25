#include <zeckendorf.h>
#include <arithmetic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// prints a list of commands to stderr and returns EXIT_FAILURE
static int help(const char *progname) {
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "%s n computes the Zeckendorf representation of n\n", progname);
	fprintf(stderr, "%s add a b ... computes the sum of the Zeckendorf representations a, b, ...\n", progname);
	fprintf(stderr, "%s mul a b ... computes the product of the Zeckendorf representations a, b, ...\n", progname);
	return EXIT_FAILURE;
}

int main(int argc, char **argv) {
	zrep *ans = NULL;

	if (argc == 2) {
		zint *n = strtoz(INT, argv[1]);
		if (n) {
			ans = z_rep(n);
			z_clear(INT, n);
		} else {
			return z_error(INT, argv[1]);
		}
	} else if (argc > 3 && (strcmp(argv[1], "add") == 0 || strcmp(argv[1], "mul") == 0)) {
		zrep *(*op)(const zrep *, const zrep *) = argv[1][0] == 'a' ? z_add : z_mul;
		zrep *z1 = strtoz(REP, argv[2]);
		zrep *z2 = strtoz(REP, argv[3]);
		if (!z1) {
			if (z2) {
				z_clear(REP, z2);
			}
			return z_error(REP, argv[2]);
		} else if (!z2) {
			z_clear(REP, z1);
			return z_error(REP, argv[3]);
		} else {
			ans = (*op)(z1, z2);
			z_clear(REP, z1);
			z_clear(REP, z2);
			for (int i = 4; i < argc; i++) {
				z1 = strtoz(REP, argv[i]);
				if (!z1) {
					z_clear(REP, ans);
					return z_error(REP, argv[i]);
				} else {
					z2 = (*op)(z1, ans);
					z_clear(REP, z1);
					z_clear(REP, ans);
					ans = z2;
				}
			}
		}
	} else {
		return help(argv[0]);
	}
	
	char *s = zrtostr(ans);
	z_clear(REP, ans);
	puts(s);
	free(s);
}
