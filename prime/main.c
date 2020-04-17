#include <stdio.h>
#include <stdlib.h>

#define limit 100000

int i, j, n, primes_count;
int numbers[limit];
int primes[limit];

static int is_n_prime() {
    if (n<limit)
        return numbers[n]^1;

    // if n is bigger than our limit, check primality of n
    for (i=0; i<primes_count; i++)
        if (n % primes[i] == 0)
            return 0;
    return 1;
}

int main(int argc, char *argv[]) {

    // sieve
    numbers[0] = 1; numbers[1] = 1;
    for (i=0, primes_count=0; i<limit; i++) {
        if (numbers[i] == 1)
             continue;
        primes[primes_count++] = i;
        for (j=2; i*j<limit; j++)
            numbers[i*j] = 1;
    }

    FILE* fp = fopen(argv[1], "r");
    while (fscanf(fp, "%d", &n) > 0)
        fprintf(stdout, "%d\n", is_n_prime());
    fclose(fp);

    return 0;
}
