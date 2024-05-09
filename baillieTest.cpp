#include <iostream>
#include <vector>
#include "functions.h"

using namespace std;
using Integer = long long;

Integer Jacobi(Integer a, Integer b)
{
    if (a == 0) return 0;
    if (a == 1) return 1;
    if (a < 0)  return (1 - (b & 2)) * Jacobi(-a, b);
    Integer a1 = a, e = 0;
    while ((a1 & 1) == 0) a1 >>= 1, ++e;
    Integer s = ((e & 1) == 0 || (b & 7) == 1 || (b & 7) == 7) ? 1 : -1;
    if ((b & 3) == 3 && (a1 & 3) == 3) s = -s;
    if (a1 == 1) return s;
    return s * Jacobi(b % a1, a1);
}

Integer generateRandom(Integer range) {
    return rand() % range;
}

int D(const Integer& n)
{
    for (int d = 5, sign = 1; ; sign = -sign, d += 2)
    {
        int dd = d * sign;
        Integer g = gcd(n, d);
        if (g > 1) return 0;  //!!! n not prime!
        if (Jacobi(dd, n) == -1) return dd;
    }
}

bool lucas(const Integer& n)
{
    if ((int)sqrt(n) * (int)sqrt(n) == n) return false;

    // The trivial cases have been verified by now.
    // Parameters:
    Integer dd = D(n), p = 1, q = (p * p - dd) / 4;

    // Decompose n+1 = d*2^s
    Integer d = n + 1, s = 0;
    while ((d & 1) == 0)
    {
        d >>= 1;
        ++s;
    }
    // lucas algorithm

    Integer u = 1, v = p, u2m = 1, v2m = p, qm = q, qm2 = q * 2, qkd = q;
    for (Integer mask = 2; mask <= d; mask <<= 1)
    {
        u2m = (u2m * v2m) % n;
        v2m = (v2m * v2m) % n;

        while (v2m < qm2) v2m += n;

        v2m -= qm2;
        qm = (qm * qm) % n;
        qm2 = qm * 2;

        if (d & mask) {
            Integer
                t1 = (u2m * v) % n,
                t2 = (v2m * u) % n,
                t3 = (v2m * v) % n,
                t4 = (((u2m * u) % n) * dd) % n;

            u = t1 + t2;
            if (u & 1) u += n;   // odd

            u = (u >> 1) % n;

            v = t3 + t4;

            if (v & 1) v += n;   // odd

            v = (v >> 1) % n;

            qkd = (qkd * qm) % n;
        }
    }

    if (u == 0 || v == 0) return true;

    Integer qkd2 = qkd * 2;
    for (Integer r = 1; r < s; ++r)
    {
        v = (v * v) % n - qkd2;
        while (v < 0) v += n;
        while (v >= n) v -= n;

        if (v == 0) return true;

        if (r < s - 1)
        {
            qkd = (qkd * 1ll * qkd) % n;
            qkd2 = qkd * 2;
        }
    }
    return false;
}

bool isPrimeBaillie(Integer n, int iteration)
{
    if (n == 0 || n == 1)
        return false;

    static Integer small_primes[] =
    { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59 };
    for (size_t i = 0; i < size(small_primes) && small_primes[i] <= n; ++i)
    {
        if (n == small_primes[i])      return true;
        if (n % small_primes[i] == 0) return false;
    }

    if (!isPrimeMiller(n, 2)) return false;

    return lucas(n);
}