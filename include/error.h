#ifndef ERROR_H
#define ERROR_H

typedef enum {BOUND, REP} zerror_t;

// z_error(err, param) prints an error message regarding param based on
// err to stderr and returns EXIT_FAILURE
int z_error(zerror_t err, const char *param);

#endif /* ERROR_H */
