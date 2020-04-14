#include <stdio.h>
#include <math.h>
#include <map>

typedef unsigned long long uint64;
std::map<uint64, int> cache;

int is_prime(uint64 n)
{
    if (n <= 1) return 0;
    else if (n <= 3) return 1;
    else if (n % 2 == 0 || n % 3 == 0) return 0;

    std::map<uint64,int>::iterator it = cache.find(n);
    if (it != cache.end())
        return it->second;

    uint64 limit = (uint64)(sqrtl(n));
    for (uint64 i=5; i<=limit; i+=6) {
        if (n % i == 0 || n % (i+2) == 0) {
            cache.insert(it, std::pair<uint64,int>(n, 0));
            return 0;
        }
    }
    cache.insert(it, std::pair<uint64,int>(n, 1));
    return 1;
}

int main(int argc, char *argv[]) {
    FILE* fp = fopen(argv[1], "r");
    uint64 i = 0;
    while (fscanf(fp, "%llu", &i) == 1) {
        fprintf(stdout, "%d\n", is_prime(i));
    }
    fclose(fp);
    return 0;
}


