#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define limit 100000
#define wlimit 316 // sqrt(limit)

unsigned char numbers[limit];

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
    int c, n;
    do {
        // fgets and atoi
        c = getc_unlocked(fp);
        if (c > '\n') {
            n = n*10 + (c - '0');
            continue;
        } else if (c == EOF && n == 0)
            break;

        // check primality of n
        if (n<limit)
            x = numbers[n];
        else {
            x = 1;
            y = sqrt(n) + 1;
            for (z=5; z<y; z+=6)
                if (n % z == 0 || n % (z+2) == 0) {
                    x = 0;
                    break;
                }
        }
        putchar_unlocked(x + '0');
        putchar_unlocked('\n');

        n = 0;
    } while (c != EOF);

    return 0;
}
