#include <stdio.h>
#include <math.h>
#include <string>
#include <iostream>

using namespace std;


string is_prime(int n)
{
    if (n <= 1) return "0";
    else if (n <= 3) return "1";
    else if (n % 2 == 0 || n % 3 == 0) return "0";

    int limit = (int)(sqrt(n));
    for (int i=5; i<=limit; i+=6) {
        if (n % i == 0 || n % (i+2) == 0)
            return "0";
    }
    return "1";
}

int main(int argc, char *argv[]) {
    FILE* fp = fopen(argv[1], "r");
    int i = 0;
    string output;
    while (fscanf(fp, "%d", &i) == 1) {
        output += is_prime(i) + "\n";
    }
    cout << output;
    fclose(fp);
    return 0;
}
