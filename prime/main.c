#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int i;
int n;
int limit;

static int is_prime()
{
    if (n <= 1) return 0;
    else if (n <= 3) return 1;
    else if (n % 2 == 0 || n % 3 == 0) return 0;

    limit = (int)(sqrt(n));
    for (i=5; i<=limit; i+=6) {
        if (n % i == 0 || n % (i+2) == 0)
            return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    FILE* fp = fopen(argv[1], "r");
    char* output = malloc(100000000*sizeof(char)); 
    char* output_start = output;
    while (fscanf(fp, "%d", &n) == 1) {
        output += sprintf(output, "%d\n", is_prime());
    }
    fprintf(stdout, "%s", output_start);
    return 0;
}
