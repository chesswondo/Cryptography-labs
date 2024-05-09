#include <vector>

using namespace std;

vector<int> prime_factors(long long int a)
{
    vector <int> res;
    for (int i = 2; i * i <= a; i++)
        while (a % i == 0)
        {
            res.push_back(i);
            a /= i;
        }

    if (a > 1) res.push_back(a);
    return res;
}

// Lezhandro symbol
int Lezhandro(long long int a, long long int p)
{
    if (a % p == 0) return 0;
    int v = 0;
    for (int i = 1; i <= (p - 1) / 2; i++)
        if ((i * a) % p > p / 2) v++;

    return 1 - 2 * (v % 2 == 1);
}

// Jacobi symbol
int Jacobi(long long int a, long long int P)
{
    int res = 1;
    for (auto e : prime_factors(P))
        res *= Lezhandro(a, e);

    return res;
}

long long generateRandom(long long range) {
    return rand() % range;
}

bool lucas_sequence(int n, int P, int Q) {
    int U0 = 0, U1 = 1, V0 = 2, V1 = P;
    int k = 1, D = P * P - 4 * Q;
    while (k <= n) {
        if (k == n) return U1 == 0;
        int U2 = P * U1 - Q * U0, V2 = P * V1 - Q * V0;
        if (U1 % 2 == 0) U2 %= n;
        else U2 = (U2 + n) % n;
        if (V1 % 2 == 0) V2 %= n;
        else V2 = (V2 + n) % n;
        U0 = U1; U1 = U2; V0 = V1; V1 = V2;
        k *= 2;
        if (k == n) return U1 == 0;
        if (D == 1) return true;
        D = (D + D) % n;
        P = (P * P - 2 * Q) % n;
        Q = (Q * Q) % n;
        if (Q < 0) Q += n;
    }
    return false;
}

bool isPrimeBaillie(long long n, int iteration)
{
    if (n == 0 || n == 1)
        return false;
    if (n == 2)
        return true;
    if (n % 2 == 0)
        return false;

    for (int k = 2, sign = 1; k<iteration+2; k++, sign *= -1)
    {
        int D = (2*k + 1) * sign;
        if (Jacobi(D, n) == -1)
        {
            int P = 1;
            int Q = (1 - D) / 4;
            if (!lucas_sequence(D, P, Q)) return false;
        }
    }

    return true;
}