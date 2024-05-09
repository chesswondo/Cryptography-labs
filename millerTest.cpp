#include <iostream>
#include "functions.h"

using Integer = long long;

// returns false if n is composite and returns true if n is probably prime
// d is an odd number
bool millerTest(Integer d, Integer n)
{
    // pick a random number in [2..n-2]
    Integer a = 2 + std::rand() % (n - 4);

    // compute a^d % n
    Integer x = mod_pow(a, d, n);

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
bool isPrimeMiller(Integer n, Integer k)
{
    // corner cases
    if (n <= 1 || n == 4)  return false;
    if (n <= 3) return true;

    // find r that n = 2^d * r + 1 for some r >= 1
    Integer d = n - 1;
    while (d % 2 == 0)
        d /= 2;

    // iterate k times
    for (Integer i = 0; i < k; i++)
        if (!millerTest(d, n))
            return false;

    return true;
}