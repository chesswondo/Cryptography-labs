#pragma once
#include<vector>

long long int mod_pow(long long int, long long int, long long int);
long long int gcd(long long int, long long int);
long long int lcm(long long int, long long int);
std::vector<int> prime_factors(long long int);
int Lezhandro(long long int, long long int);
int Jacobi(long long int, long long int);
long long generateRandom(long long);
bool isPrimeBaillie(long long, int);
bool millerTest(long long int, long long int);
bool isPrimeMiller(long long int, long long int);
long long generate_prime_number(int, int);

void process_task1();
void process_task2();