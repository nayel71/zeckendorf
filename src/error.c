#include "../include/error.h"
#include <stdio.h>
#include <stdlib.h>

// message(err) returns an error message based on the type of err
static const char *message(zerror_t err) {
	switch (err) {
		case ARG: return "invalid argument";
		case REP: return "invalid Zeckendorf representation";
	}
}

int z_error(zerror_t err, const char *param) {
	fprintf(stderr, "Zeckendorf Error: %s %s\n", message(err), param);
	return EXIT_FAILURE;
}
