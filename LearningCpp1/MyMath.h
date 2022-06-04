#pragma once
#include <vector>
//extern "C" int add(int, int);

extern "C"
{
	int add(int, int);
	int substract(int, int);
}
float add(float, float);
int factorial(uint32_t);
std::vector<int> fibonacci_series(uint32_t n);
int fib_power(int);






/*
Inline functions are a suggestion for the compiler.
Compiler can make functions inline automatically in "RELEASE" mode.
It is kind a micro optimization.
Inline function is replacement for macro function. It is better than macro for type checking.
Inline eliminates function call overhead by copying function body into another function.
It removes function from assembly so that it makes hard to debug.
It may cause some linker errors and increases program size.
*/
// #define square(x) x*x // it is a macro function. DON'T USE IT.
inline int square(int x)
{
	return x * x;
}