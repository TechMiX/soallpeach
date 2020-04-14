#include <iostream>
#include <fstream>
#include <openssl/bn.h>
#include <string>

using namespace std;

bool FermatProbablePrimalityTest(string number)
{
    if (number == "2")
        return true;

    BN_CTX *bnctx = BN_CTX_new();

    BIGNUM *a = BN_new();
    BN_dec2bn(&a, string("2").c_str());

    BIGNUM *n = BN_new();
    BN_dec2bn(&n, number.c_str());

    BIGNUM *e = BN_new();
    BN_sub(e, n, BN_value_one());

    BIGNUM *r = BN_new();

    BN_mod_exp(r, a, e, n, bnctx);

    if (BN_cmp(r, BN_value_one()) == 0)
        return true;

    return false;
}

int main(int argc, char *argv[]) {
    ifstream f(argv[1]);
    if (f.is_open())
    {
        string line;
        while ( getline(f, line) )
        {
            cout << FermatProbablePrimalityTest(line)? 1 : 0;
            cout << endl;
        }
        f.close();
    } else
        cout << "Unable to open file"; 
    return 0;
}
