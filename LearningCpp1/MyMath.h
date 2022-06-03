#pragma once
//extern "C" int add(int, int);

extern "C"
{
	int add(int, int);
	int substract(int, int);
}
float add(float, float);
int factorial(uint32_t);
std::vector<int> fibonacci_series(uint32_t);
int fib_power(int);
