#include <iostream>
#include <vector>
#include "functions.h"
#include "millerTest.h"

using namespace std;

long long carmichael(long long n)
{
    long long k = 2;
    long long a = 1;
    long long timer = 0;
    vector<long long> alist;

    while (!(gcd(a, n) == 1)) a++;

    while (gcd(a, n) == 1 && a <= n)
    {
        alist.push_back(a);
        a++;
        while (!(gcd(a, n) == 1)) a++;
    }

    timer = alist.size();
    while (timer >= 0)
        for (long long a : alist)
        {
            if (mod_pow(a, k, n) == 1)
            {
                timer--;
                if (timer < 0) break;
            }
            else
            {
                timer = alist.size();
                k++;
            }
        }

    return k;
}

long long mul_inv(long long a, long long b)
{
    long long b0 = b, t, q;
    long long x0 = 0, x1 = 1;
    if (b == 1) return 1;
    while (a > 1) {
        q = a / b;
        t = b, b = a % b, a = t;
        t = x0, x0 = x1 - q * x0, x1 = t;
    }
    if (x1 < 0) x1 += b0;
    return x1;
}

class RSA
{
private:
    int bit_length, k;
    long long p, q, n, lambda, d, e;

public:
    RSA(int bit_length = 20, int k = 5)
    {
        this->bit_length = bit_length;
        this->k = k;
        this->p = generate_prime_number(bit_length, k);
        this->q = generate_prime_number(bit_length, k);
        this->n = this->p * this->q;
        this->lambda = lcm(carmichael(this->q), carmichael(this->p));
        long long range = this->lambda - 3;
        long long e;
        while (true)
        {
            long long random_number = rand() % range + 2;
            if (isPrimeMiller(random_number, 5) && this->lambda % random_number != 0) { e = random_number; break; }
        }
        this->e = e;
        this->d = mul_inv(e, lambda);

        cout << "p = " << p << ", q = " << q << ", n = " << n << endl;
        cout << "Carmichael(" << n << ") = " << lambda << endl;
        cout << "e = " << e << endl;
        cout << "d = " << d << endl;
    }

    //friend long long carmichael(long long n);
    //friend long long mul_inv(long long a, long long b);
    //friend long long generate_prime_number(int, int);
};

void process_task2()
{
    RSA rsa(23, 4);
}