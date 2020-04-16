#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#define limit 100000

int i, j, n, l, r, m;
int primes_count;
bool numbers[limit];
int primes[limit];

static void sieve() {
    numbers[0] = true; numbers[1] = true;
    for (i=0, primes_count=0; i<limit; i++) {
	if (numbers[i] == true) continue;
        primes[primes_count++] = i;
        for (j=2; i*j<limit; j++) numbers[i*j] = true;
    }
}

static int is_n_prime() {
    if (n <= 1) return 0;
    else if (n <= 3) return 1;
    else if (n % 2 == 0 || n % 3 == 0) return 0;

    // binary search in primes
    l = 0; r = primes_count - 1;
    while (l <= r) {
        m = l + (r - l) / 2;
        if (primes[m] == n) return 1;
        if (primes[m] < n) l = m + 1;
        else r = m - 1;
    }

    // if n is bigger than our limit, check primality of n
    if (n < limit) return 0;
    j = (int)(sqrt(n));
    for (i=5; i<=j; i+=6) {
        if (n % i == 0 || n % (i+2) == 0)
            return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    sieve();
    FILE* fp = fopen(argv[1], "r");
    while (fscanf(fp, "%d", &n) == 1) {
        fprintf(stdout, "%d\n", is_n_prime());
    }
    return 0;
}
