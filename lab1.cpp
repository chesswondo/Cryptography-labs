#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "functions.h"

using namespace std;
using Integer = long long;

Integer generate_prime_number(int bit_length, int k)
{
    if (bit_length < 4) throw invalid_argument("received too small value of bit length. Cannot generate prime number.");
    bit_length = min(bit_length, 63);
    Integer min_value = pow(2, bit_length - 1);
    Integer max_value = pow(2, bit_length) - 1;
    Integer range = max_value - min_value;
    while (true)
    {
        Integer random_number = rand() % range + min_value;
        if (isPrimeMiller(random_number, k)) return random_number;
    }
}

string base64(unsigned char* f, size_t s)
{
    string res;
    static const unsigned char codes64[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
    const int PADSYM = 64;
    for (size_t i = 0; i < s;)
    {
        unsigned char src[3] = { 0 };
        unsigned char dest[4];
        int gcount = 0;
        if (i++ < s) { src[0] = *f++; gcount++; }
        if (i++ < s) { src[1] = *f++; gcount++; }
        if (i++ < s) { src[2] = *f++; gcount++; }
        switch (gcount)
        {
        case 0:
            return res; // No symbol
        case 3:
            dest[3] = codes64[src[2] & 0x3F];
            dest[2] = codes64[((src[1] << 2) | (src[2] >> 6)) & 0x3F];
            break;
        case 2:
            dest[3] = codes64[PADSYM];
            dest[2] = codes64[((src[1] << 2) | (src[2] >> 6)) & 0x3F];
            break;
        case 1:
            dest[2] = dest[3] = codes64[PADSYM];
            break;
        default: /*assert(!"illegal gcount")*/;
        }
        dest[1] = codes64[((src[0] << 4) | (src[1] >> 4)) & 0x3F];
        dest[0] = codes64[(src[0] >> 2) & 0x3F];
        for (int j = 0; j < 4; ++j) res += dest[j];
    }
    return res;
}

string bytes(unsigned char* f, size_t s)
{
    ostringstream out;
    for (int i = 0; i < s; ++i)
    {
        out << "0x" << hex << setfill('0') << setw(2) << int(*(f + i));
        if (i != s - 1) out << " ";
    }
    return out.str();
}

void process_task1()
{
    int k, totalMiller = 0, totalBaillie = 0, bit_length;

    cout << "Enter k (the number of iterates):\n";
    cin >> k;
    cout << "Enter bit length of prime number to generate:\n";
    cin >> bit_length;
    
    try {
        Integer gen_prime = generate_prime_number(bit_length, k);
        string prime_base2;
        Integer gen_prime_copy = gen_prime;
        do {
            prime_base2 = to_string(gen_prime_copy & 1) + prime_base2;
        } while (gen_prime_copy >>= 1);

        cout << "\nGenerated prime number:\n" << "base2: " << prime_base2 << endl;
        cout << "base10: " << gen_prime << endl;
        cout << "base64: " << base64((unsigned char*)&gen_prime, sizeof(gen_prime)) << endl;
        cout << "byte[]: " << bytes((unsigned char*)&gen_prime, sizeof(gen_prime)) << endl;

    } catch (exception& e) { cerr << "Exception: " << e.what() << endl; }

    // test section
    cout << endl;
    (isPrimeMiller(93553, k))  ? cout << "Miller test 1 passed" << endl : cout << "Miller test 1 failed" << endl;
    (!isPrimeMiller(14685, k)) ? cout << "Miller test 2 passed" << endl : cout << "Miller test 2 failed" << endl;
    (isPrimeMiller(81677, k))  ? cout << "Miller test 3 passed\n" << endl : cout << "Miller test 3 failed\n" << endl;

    (isPrimeBaillie(93553, k))  ? cout << "Baillie test 1 passed" << endl : cout << "Baillie test 1 failed" << endl;
    (!isPrimeBaillie(14685, k)) ? cout << "Baillie test 2 passed" << endl : cout << "Baillie test 2 failed" << endl;
    (isPrimeBaillie(81677, k))  ? cout << "Baillie test 3 passed" << endl : cout << "Baillie test 3 failed" << endl;

    for (int i = 0; i < 100000; i++)
    {
        if (isPrimeMiller(i, k))
            totalMiller++;
        if (isPrimeBaillie(i, k))
            totalBaillie++;
    }

    cout << "\nAll prime numbers Miller test found with k = " << k << " from 1 to 100000:\n" << totalMiller << endl;
    cout << "\nAll prime numbers Baillie test found with k = " << k << " from 1 to 100000:\n" << totalBaillie << endl;

    cout << "\nRight number is 9592\n\n";
}