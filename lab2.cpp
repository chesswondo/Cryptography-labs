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
    long long p, q, lambda, d;

public:
    long long e, n;
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

    vector<long long> encrypt(vector <long long>& msg)
    {
        vector <long long> result;
        for (long long s: msg)
        {
            long long encrypted_symbol = mod_pow(s, this->e, this->n);
            result.push_back(encrypted_symbol);
        }
        return result;
    }

    vector<long long> decrypt(vector <long long>& msg)
    {
        vector <long long> result;
        for (long long s : msg)
        {
            long long x1 = mod_pow(s, this->d % (this->p - 1), this->p);
            long long x2 = mod_pow(s, this->d % (this->q - 1), this->q);
            vector<long long> x = { x1, x2 };
            vector<long long> b = { this->p, this->q };
            long long p_inv = mul_inv(this->p, this->q);
            long long q_inv = mul_inv(this->q, this->p);
            result.push_back((p_inv * this->p * x2 + q_inv * this->q * x1) % this->n);
        }
        return result;
    }
};

void process_task2()
{
    RSA rsa(20, 4);
    vector<long long> message = { 123, 456, 21, 89 };
    cout << "Message is: ";
    for (auto s : message) cout << s << " ";
    cout << endl;
    vector<long long> enc_message = rsa.encrypt(message);
    cout << "Encrypted message is: ";
    for (auto s : enc_message) cout << s << " ";
    cout << endl;
    vector<long long> dec_message = rsa.decrypt(enc_message);
    cout << "Decrypted message is: ";
    for (auto s : dec_message) cout << s << " ";
    cout << "\n\n";
}