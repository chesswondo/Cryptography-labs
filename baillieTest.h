#pragma once
#include "millerTest.h"

inline long long generateRandom(long long range) {
    return rand() % range;
}

inline bool isPrimeBaillie(long long n, int iteration) {
    if (n == 0 || n == 1)
        return false;
    if (n == 2)
        return true;
    if (n % 2 == 0)
        return false;

    for (int i = 0; i < iteration; i++) {
        long long a = generateRandom(n - 1) + 1;
        if (mod_pow(a, n - 1, n) != 1)
            return false;
    }
    return true;
}