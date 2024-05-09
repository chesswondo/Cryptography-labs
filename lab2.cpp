#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "functions.h"

using namespace std;
using Integer = long long;

Integer carmichael(Integer n)
{
    Integer k = 2;
    Integer a = 1;
    Integer timer = 0;
    vector<Integer> alist;

    while (!(gcd(a, n) == 1)) a++;

    while (gcd(a, n) == 1 && a <= n)
    {
        alist.push_back(a);
        a++;
        while (!(gcd(a, n) == 1)) a++;
    }

    timer = alist.size();
    while (timer >= 0)
        for (Integer a : alist)
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

class RSA
{
private:
    int bit_length, k;
    Integer p, q, lambda, d;

public:
    Integer e, n;
    RSA(int bit_length = 20, int k = 5, bool print = false)
    {
        this->bit_length = bit_length;
        this->k = k;
        do
        {
            this->p = generate_prime_number(bit_length/2, k);
            this->q = generate_prime_number(bit_length/2, k);
        } while (this->q == this->p);
        
        this->n = this->p * this->q;
        this->lambda = lcm(carmichael(this->q), carmichael(this->p));
        Integer range = this->lambda - 3;
        Integer e;
        while (true)
        {
            Integer random_number = rand() % range + 2;
            if (isPrimeMiller(random_number, 5) && this->lambda % random_number != 0) { e = random_number; break; }
        }
        this->e = e;
        this->d = mul_inv(e, lambda);

        if (print)
        {
            cout << "p = " << p << ", q = " << q << ", n = " << n << endl;
            cout << "carmichael(" << n << ") = " << lambda << endl;
            cout << "e = " << e << endl;
            cout << "d = " << d << endl;
        }
    }

    vector<Integer> encrypt(vector <Integer>& msg)
    {
        vector <Integer> result;
        for (Integer s: msg)
        {
            Integer encrypted_symbol = mod_pow(s, this->e, this->n);
            result.push_back(encrypted_symbol);
        }
        return result;
    }

    vector<Integer> decrypt(vector <Integer>& msg)
    {
        vector <Integer> result;
        for (Integer s : msg)
        {
            Integer x1 = mod_pow(s, this->d % (this->p - 1), this->p);
            Integer x2 = mod_pow(s, this->d % (this->q - 1), this->q);
            vector<Integer> x = { x1, x2 };
            vector<Integer> b = { this->p, this->q };
            Integer p_inv = mul_inv(this->p, this->q);
            Integer q_inv = mul_inv(this->q, this->p);
            result.push_back((p_inv * this->p * x2 + q_inv * this->q * x1) % this->n);
        }
        return result;
    }
};

void process_task2()
{
    int bit_length;
    cout << "Enter bit length of prime numbers to generate (-1 to test execution time depending on different bit lengths):\n";
    cin >> bit_length;
    cin.ignore(1024, '\n');

    string message;
    cout << "Write your message:\n";
    getline(cin, message);
    cout << "\nMessage is: " << message;

    if (bit_length != -1)
    {
        // starting timepoint
        auto start = chrono::high_resolution_clock::now();

        cout << "\n\n";
        RSA rsa(bit_length, 10, true);
        vector<Integer> num_message;
        for (char s : message) num_message.push_back(static_cast<int>(s));

        vector<Integer> enc_message = rsa.encrypt(num_message);
        vector<Integer> dec_message = rsa.decrypt(enc_message);

        // ending timepoint
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

        cout << "\nEncrypted message is: ";
        for (auto s : enc_message) cout << s << " ";
        cout << "\nDecrypted message is: ";
        for (auto s : dec_message) cout << static_cast<char>(s);

        cout << "\nTime taken by algorithm: "
            << duration.count() << " microseconds\n\n";
    }

    else
    {
        cout << "\n\n";
        vector <int> bit_lengths = { 10, 15, 20, 25, 30 };
        for (int bl : bit_lengths)
        {
            int average_duration = 0;
            for (int i = 0; i < 10; i++)
            {
                auto start = chrono::high_resolution_clock::now();

                RSA rsa(bl, 10);
                vector<Integer> num_message;
                for (char s : message) num_message.push_back(static_cast<int>(s));

                vector<Integer> enc_message = rsa.encrypt(num_message);
                vector<Integer> dec_message = rsa.decrypt(enc_message);

                auto stop = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
                average_duration += duration.count();
            }
            average_duration /= 10;
            cout << "Average time taken for " << bl << " bit length: " << average_duration << " microseconds\n";
        }
        cout << endl;
    }
}