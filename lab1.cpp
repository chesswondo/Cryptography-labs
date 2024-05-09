#include <cstdlib>
#include <iostream>
#include "functions.h"
#include <string>

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
        cout << "byte[]: " << static_cast<void*>(&gen_prime) << endl;

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