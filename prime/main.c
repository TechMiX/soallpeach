#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define limit 100000

int i, j, n;
int primes_count;
bool numbers[limit];
int primes[limit];

static void sieve() {
    numbers[0] = true; numbers[1] = true;
    for (i=0, primes_count=0; i<limit; i++) {
	if (numbers[i])
             continue;
        primes[primes_count++] = i;
        for (j=2; i*j<limit; j++) numbers[i*j] = true;
    }
}

static int is_n_prime() {
    if (n<limit)
        return !numbers[n]? 1 : 0;

    // if n is bigger than our limit, check primality of n
    for (i=0; i<primes_count; i++)
        if (n % primes[i] == 0)
            return 0;
    return 1;
}

int main(int argc, char *argv[]) {
    sieve();
    FILE* fp = fopen(argv[1], "r");
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *fcontent = malloc(fsize + 1);
    i = fread(fcontent, 1, fsize, fp);

    char* output = (char*)malloc(3000000*sizeof(char)); 
    char* output_start = output;
    FILE* fpm = fmemopen(fcontent, fsize, "r");
    while (fscanf(fpm, "%d", &n) > 0)
        output += sprintf(output, "%d\n", is_n_prime());
    fprintf(stdout, "%s", output_start);
    return 0;
}
