#include <iostream>

// calculate (n^exp) % mod
long long int mod_pow(long long int n, long long int exp, long long int mod)
{
    long long int res = 1;
    while (exp > 0)
    {
        if (exp % 2) res = (res * n) % mod;
        exp /= 2;
        n = (n * n) % mod;
    }
    return res;
}

// returns false if n is composite and returns true if n is probably prime
// d is an odd number
bool millerTest(long long int d, long long int n)
{
    // pick a random number in [2..n-2]
    long long int a = 2 + std::rand() % (n - 4);

    // compute a^d % n
    long long int x = mod_pow(a, d, n);

    if (x == 1 || x == n - 1)
        return true;

    while (d != n - 1)
    {
        x = (x * x) % n;
        d *= 2;

        if (x == 1) return false;
        if (x == n - 1) return true;
    }

    return false;
}

// returns false if n is composite and returns true if n is probably prime
bool isPrimeMiller(long long int n, long long int k)
{
    // corner cases
    if (n <= 1 || n == 4)  return false;
    if (n <= 3) return true;

    // find r that n = 2^d * r + 1 for some r >= 1
    long long int d = n - 1;
    while (d % 2 == 0)
        d /= 2;

    // iterate k times
    for (long long int i = 0; i < k; i++)
        if (!millerTest(d, n))
            return false;

    return true;
}