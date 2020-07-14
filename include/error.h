#ifndef ERROR_H
#define ERROR_H

typedef enum {ARG, REP} zerror_t;

// z_error(err, param) prints an error message regarding param based on
// the type of err to stderr and returns EXIT_FAILURE
// effects: prints output
int z_error(zerror_t err, const char *param);

#endif /* ERROR_H */
