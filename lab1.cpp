#include <cstdlib>
#include <iostream>
#include "functions.h"
#include "millerTest.h"
#include "BaillieTest.cpp"

using namespace std;

void process_task1()
{
    int k, total = 0;

    cout << "Enter k (the number of iterates):\n";
    cin >> k;

    // test section
    cout << endl;
    (isPrimeMiller(93553, k))  ? cout << "Test 1 passed" << endl : cout << "Test 1 failed" << endl;
    (!isPrimeMiller(14685, k)) ? cout << "Test 2 passed" << endl : cout << "Test 2 failed" << endl;
    (isPrimeMiller(81677, k))  ? cout << "Test 3 passed" << endl : cout << "Test 3 failed" << endl;

    cout << "\nAll prime numbers program found with k = " << k << " from 1 to 10000:\n";

    for (int i = 0; i < 10000; i++)
        if (isPrimeMiller(i, k))
        {
            cout << i << " ";
            total++;
        }

    cout << "\nTotal: " << total << endl;
    cout << "Right number is 1229\n"; //9592 for 100000
}