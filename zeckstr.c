#include "zeckendorf.h"

// maxfib(n, index, fib) computes the largest Fibonacci number <= n,
// stores it at fib and stores its index at index
static void maxfib(const int n, int *index, int *fib) {
	int fib1 = 0;
	int fib2 = 1;
	int new = fib1 + fib2;
	for (*index = 1; new <= n; (*index)++) {
		fib1 = fib2;
		fib2 = new;
		new = fib1 + fib2;
	}
	*fib = fib2;
}

char *zeckendorf(const int n) {
	int index, newindex, fib, i = 0, m = n;
	maxfib(n, &index, &fib);
	char *ans = malloc(index * sizeof(char));
	while (m > 0) {
		m -= fib;
		maxfib(m, &newindex, &fib);
		ans[i] = one;
		i++;
		for (int j = index - 1; j > newindex; j--) {
			ans[i] = zero;
			i++;
		}
		maxfib(m, &index, &fib);
	} 
	ans[i] = '\0'; // at this point i = original index - 1 
	return ans;
}
