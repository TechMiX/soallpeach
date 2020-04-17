#include <stdio.h>
#include <stdlib.h>

#define limit 100000

int main(int argc, char *argv[]) {

    int i, j, n, primes_count;
    int numbers[limit];
    int primes[limit];

    // sieve
    numbers[0] = 1; numbers[1] = 1;
    for (i=0, primes_count=0; i<limit; i++) {
        if (numbers[i] == 1)
             continue;
        primes[primes_count++] = i;
        for (j=2; i*j<limit; j++) numbers[i*j] = 1;
    }

    // open and read the whole file at once
    FILE* fp = fopen(argv[1], "r");
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *fcontent = malloc(fsize + 1);
    i = fread(fcontent, 1, fsize, fp);

    char* output = malloc(3000000*sizeof(char)); 
    char* output_start = output;
    FILE* fpm = fmemopen(fcontent, fsize, "r");
    while (fscanf(fpm, "%d", &n) > 0) {
        if (n<limit) {
            output += sprintf(output, "%d\n", numbers[n]^1);
            continue;
        }

        // if n is bigger than our limit, check primality of n
        for (i=0; i<primes_count; i++)
            if (n % primes[i] == 0) {
                output += sprintf(output, "%d\n", 0);
                continue;
            }
        output += sprintf(output, "%d\n", 1);
    }
    fprintf(stdout, "%s", output_start);
    return 0;
}
