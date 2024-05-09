#include <iostream>

using Integer = long long;

// calculate (n^exp) % mod
Integer mod_pow(Integer n, Integer exp, Integer mod)
{
    Integer res = 1;
    while (exp > 0)
    {
        if (exp % 2) res = (res * n) % mod;
        exp /= 2;
        n = (n * n) % mod;
    }
    return res;
}

Integer gcd(Integer a, Integer b)
{
    while (a && b)
        if (a < b) b %= a;
        else a %= b;

    return a + b;
}

Integer lcm(Integer a, Integer b)
{
    return a / gcd(a, b) * b;
}

Integer mul_inv(Integer a, Integer b)
{
    Integer b0 = b, t, q;
    Integer x0 = 0, x1 = 1;
    if (b == 1) return 1;
    while (a > 1) {
        q = a / b;
        t = b, b = a % b, a = t;
        t = x0, x0 = x1 - q * x0, x1 = t;
    }
    if (x1 < 0) x1 += b0;
    return x1;
}