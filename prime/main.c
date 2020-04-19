#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define limit 100000
#define wlimit 316 // sqrt(limit)

int i, j, n;
unsigned char numbers[limit];

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
    int x, y, z;
    for (x=1; x<=wlimit; x++)
        for (y=1; y<=wlimit; y++) {
            z = 4*x*x + y*y;
            if (z <= limit && (
                z % 60 == 1 || z % 60 == 13 || z % 60 == 17 || z % 60 == 29 ||
                z % 60 == 37 || z % 60 == 41 || z % 60 == 49 || z % 60 == 53)
               )
                numbers[z] = !numbers[z];
            z = 3*x*x + y*y;
            if (z <= limit && (
                z % 60 == 7 || z % 60 == 19 || z % 60 == 31 || z % 60 == 43)
               )
                numbers[z] = !numbers[z];
            z = 3*x*x - y*y;
            if (x > y && z <= limit && (
                z % 60 == 11 || z % 60 == 23 || z % 60 == 47 || z % 60 == 59)
               )
                numbers[z] = !numbers[z];
        }
    numbers[1] = numbers[4] = 0;
    numbers[2] = numbers[3] = numbers[5] = 1;

    FILE* fp = fopen(argv[1], "r");
    char data[wlimit];
    int c;
    do {
        // fgets and atoi
        c = getc_unlocked(fp);
        if (c > '\n') {
            n = n*10 + (c - '0');
            continue;
        } else if (c == EOF && n == 0)
            break;

        putchar_unlocked(is_n_prime() + '0');
        putchar_unlocked('\n');

        n = 0;
    } while (c != EOF);

    return 0;
}
