#include "../include/zeckendorf.h"
#include <stdlib.h>

// maxfib(n, index, fib) computes the largest Fibonacci number <= n,
// stores it at fib and stores its index at index
static void maxfib(const zint n, int *index, zint *fib) {
	zint fib1 = 0;
	zint fib2 = 1;
	for (*index = 1; fib1 + fib2 <= n; (*index)++) {
		*fib = fib1 + fib2;
		fib1 = fib2;
		fib2 = *fib;
	}
}

zrep z_rep(const zint n) {
	int index;
	zint fib;
	maxfib(n, &index, &fib);

	zrep ans = malloc(index * sizeof(zdigit));

	int i = 0;
	zint rem = n;
	for (int next_index; rem > 0; maxfib(rem, &index, &fib)) {
		rem -= fib;
		maxfib(rem, &next_index, &fib);
		ans[i] = ONE;
		i++;
		for (int j = index - 1; j > next_index; j--, i++) {
			ans[i] = ZERO;
		}
		
	} 
	ans[i] = '\0'; // at this point, i == original index - 1 
	return ans;
}
