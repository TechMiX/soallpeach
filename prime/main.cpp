#include <stdio.h>
#include <math.h>

typedef unsigned long long uint64;

int is_prime(uint64 n)
{
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0) return 0;

    uint64 limit = (uint64)(sqrtl(n));
    for (uint64 i=2; i<limit; i++) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    FILE* fp = fopen(argv[1], "r");
    uint64 i = 0;
    while (!feof(fp)) {
        fscanf(fp, "%llu", &i);
        printf("%d\n", is_prime(i));
    }
    fclose(fp);
    return 0;
}


