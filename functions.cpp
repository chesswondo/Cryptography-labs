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

long long int gcd(long long int a, long long int b)
{
    while (a && b)
        if (a < b) b %= a;
        else a %= b;

    return a + b;
}

long long int lcm(long long int a, long long int b)
{
    return a / gcd(a, b) * b;
}