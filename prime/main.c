#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define limit 100000
#define wlimit 316 // sqrt(limit)

int i, j, n, primes_count;
unsigned char numbers[limit];
int primes[limit];

static int is_n_prime() {
    if (n<limit)
        return numbers[n];

    // if n is bigger than our limit, check primality of n
    j = (int) sqrt(n) + 1;
    for (i=5; i<j; i+=6)
        if (n % i == 0 || n % (i+2) == 0)
            return 0;
    return 1;
}

int main(int argc, char *argv[]) {

    // sieve of atkin
    int k, x, y, z, g, h;
    for (x=1; x<=wlimit; x++)
        for (y=1; y<=wlimit; y++) {
            g = x*x;
            h = y*y;
            z = 4*g+h;
            if (z <= limit && (
                z % 60 == 1 || z % 60 == 13 || z % 60 == 17 || z % 60 == 29 ||
                z % 60 == 37 || z % 60 == 41 || z % 60 == 49 || z % 60 == 53)
               )
                numbers[z] = !numbers[z];
            z -= g;
            if (z <= limit && (
                z % 60 == 7 || z % 60 == 19 || z % 60 == 31 || z % 60 == 43)
               )
                numbers[z] = !numbers[z];
            z -= 2*h;
            if (x > y && z <= limit && (
                z % 60 == 11 || z % 60 == 23 || z % 60 == 47 || z % 60 == 59)
               )
                numbers[z] = !numbers[z];
        }

    for (i=5; i<=wlimit; i++)
        if (numbers[i] == 1)
            for (j=1; j*i*i<=limit; j++)
                numbers[j*i*i] = 0;

    numbers[0] = 0; numbers[1] = 0; numbers[2] = 1; numbers[3] = 1; numbers[4] = 0; numbers[5] = 1;

    FILE* fp = fopen(argv[1], "r");
    while (fscanf(fp, "%d", &n) > 0)
        fprintf(stdout, "%d\n", is_n_prime());
    fclose(fp);

    return 0;
}
