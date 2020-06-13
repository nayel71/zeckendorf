#include "../include/zeckendorf.h"

// maxfib(n, index, fib) computes the largest Fibonacci number <= n,
// stores it at fib and stores its index at index
static void maxfib(const int n, int *index, int *fib) {
	int fib1 = 0, fib2 = 1;
	for (*index = 1; fib1 + fib2 <= n; (*index)++) {
		*fib = fib1 + fib2;
		fib1 = fib2;
		fib2 = *fib;
	}
}

char *zeckendorf(const int n) {
	int index, fib, i = 0;
	maxfib(n, &index, &fib);
	char *ans = malloc(index * sizeof(char));
	for (int next_index, m = n; m > 0; maxfib(m, &index, &fib)) {
		m -= fib;
		maxfib(m, &next_index, &fib);
		ans[i] = ONE;
		i++;
		for (int j = index - 1; j > next_index; j--, i++) {
			ans[i] = ZERO;
		}
		
	} 
	ans[i] = '\0'; // at this point, i = original index - 1 
	return ans;
}
