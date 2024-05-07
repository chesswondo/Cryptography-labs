#include <cstdlib>
#include <iostream>
#include "functions.h"
#include "millerTest.h"
#include "baillieTest.h"

using namespace std;

long long generate_prime_number(int bit_length, int k)
{
    bit_length = min(bit_length, 63);
    int half_bit_length = bit_length / 2;
    long long min_value = pow(2, half_bit_length - 1);
    long long max_value = pow(2, half_bit_length) - 1;
    long long range = max_value - min_value;
    while (true)
    {
        long long random_number = rand() % range + min_value;
        if (isPrimeMiller(random_number, k)) return random_number;
    }
}

void process_task1()
{
    int k, totalMiller = 0, totalBaillie = 0;

    cout << "Enter k (the number of iterates):\n";
    cin >> k;

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