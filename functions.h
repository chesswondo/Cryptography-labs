#pragma once

using Integer = long long;

Integer mod_pow(Integer, Integer, Integer);
Integer gcd(Integer, Integer);
Integer lcm(Integer, Integer);
Integer Jacobi(Integer, Integer);
Integer generateRandom(Integer);
bool isPrimeBaillie(Integer);
bool millerTest(Integer, Integer);
bool isPrimeMiller(Integer, Integer);
Integer generate_prime_number(int, int);
Integer mul_inv(Integer, Integer);

void process_task1();
void process_task2();