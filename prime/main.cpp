#include <iostream>
#include <fstream>
#include <openssl/bn.h>
#include <string>

using namespace std;

BN_CTX *bnctx;
BIGNUM *a;
BIGNUM *n;
BIGNUM *e;
BIGNUM *r;

string is_prime(string number)
{
    if (number == "2")
	return "1";

    // Fermat Primality Test
    BN_dec2bn(&n, number.c_str());
    BN_sub(e, n, BN_value_one());
    BN_mod_exp(r, a, e, n, bnctx);
    if (BN_cmp(r, BN_value_one()) == 0)
        return "1";

    return "0";
}

int main(int argc, char *argv[]) {

    ifstream f(argv[1]);
    if (f.is_open()) {
        string line, output;
        bnctx = BN_CTX_new();
        a = BN_new();
        BN_dec2bn(&a, string("2").c_str());
        n = BN_new();
        e = BN_new();
        r = BN_new();
        while ( getline(f, line) ) {
            output += is_prime(line) + "\n";
        }
        cout << output;
        f.close();
    } else
        cout << "Unable to open file";

    return 0;
}
