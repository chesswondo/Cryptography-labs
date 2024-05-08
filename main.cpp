#include <iostream>
#include <vector>
#include <cmath>
#include <time.h>

#include "functions.h"

using namespace std;

int main()
{
    srand(time(NULL));
    int num_task;
    while (true)
    {
        cout << "Enter the number of lab you want to process:\n";
        cin >> num_task;
        cin.ignore(100, '\n');

        switch (num_task)
        {
        case 1:
            process_task1();
            break;

        case 2:
            process_task2();
            break;

        default:
            cout << "Incorrect number, retry\n\n";
            break;
        }

    }

    return 0;
}