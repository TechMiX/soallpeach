#include <stdio.h>
#include <cmath>

using namespace std;

typedef unsigned long long uint64;

bool FermatProbablePrimalityTest(uint64 n)
{
    if (n == uint64(2))
        return true;
    uint64 a = 2;
    uint64 e = n - 1;
    uint64 r;
    r = uint64(pow(a, e)) % n;
    if (r == 1)
        return true;

    return false;
}

int main(int argc, char *argv[]) {
    FILE* fp = fopen(argv[1], "r");
    uint64 i = 0;
    while (!feof(fp))
    {
        fscanf(fp, "%d", &i);
        printf("%d\n", FermatProbablePrimalityTest(i)? 1 : 0);
    }
    fclose(fp);
    return 0;
}


