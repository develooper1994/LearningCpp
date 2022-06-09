#include <iostream>
#include <vector>
/*
<h1> Function Overloading < / h1>
1.Confusion resolved in ***compile-time*** with "Name Mangling"
2."Name Mangling"= Compiler generates unique names for functions.
This allows linker to link the call with the correct overload function.
It varies from compiler to compiler
3."Name Mangling" suppressed with "extern "C"" on global functions and variables.
Using extern C on a C++ functions allows us to call that function from C or other languages.

***
* "extern "C"" must be applied on the definition and declaration.
* If you just apply "extern "C"" onto declaration but not onto implementation, it compiles but throws a linker error because function name is mangled and linked can't find it.
***

*/

//extern "C" int add(int x, int y)
//{
//	return x + y;
//}
extern "C" {
	int add(int x = 0, int y = 0)
	{
		return x + y;
	}
	int substract(int x, int y)
	{
		return x - y;
	}
}
int add(const int& x, const int& y)
{
	return x + y;
}
float add(float x, float y)
{
	return x + y;
}
float add(float x, int y)
{
	return float(x + y);
}

int factorial(uint32_t x)
{
	if (x < 0)
	{
		std::cerr << "Error! Factorial of a negative number doesn't exist.";
		return -1;
	}
	int temp = 1;
	for (size_t i = 1; i < x; ++i)
	{
		temp *= i;
	}
	return temp;
}

std::vector<int> fibonacci_series(uint32_t n)
{
	// 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, ……..
	int temp1 = 0, temp2 = 1, next = 0;
	std::vector<int> vec;
	if (n == 0)
	{
		vec.push_back(temp1);
		return vec;
	}

	for (size_t i = 1; i < n - 1; ++i)
	{
		if (i == 1)
		{
			vec.push_back(temp1);
			std::cout << temp1 << ", ";
		}
		if (i == 2)
		{
			std::cout << temp2 << ", ";
		}

		next = temp1 + temp2;
		temp1 = temp2;
		temp2 = next;
		vec.push_back(next);

		if (i % 16 == 15)
		{
			// enter the new line
			std::cout << "\n";
		}
		std::cout << next << ", ";
	}
	return vec;
}


/*
	Fibonacci with matrix multiply
	There is some math involved.
*/
void multiply(int F[2][2])
{
	int x = F[0][0] * F[0][0] +
		F[0][1] * F[1][0];
	int y = F[0][0] * F[0][1] +
		F[0][1] * F[1][1];
	int z = F[1][0] * F[0][0] +
		F[1][1] * F[1][0];
	int w = F[1][0] * F[0][1] +
		F[1][1] * F[1][1];

	F[0][0] = x;
	F[0][1] = y;
	F[1][0] = z;
	F[1][1] = w;
}
void power(int F[2][2], int n)
{
	// optimized(halving method)
	if (n == 0 || n == 1)
	{
		return;
	}
	power(F, n / 2);
	multiply(F);

	// unoptimized
	/*for (size_t i = 2; i < n; ++i)
	{
		multiply(F);
	}*/
}
int fib_power(int n)
{
	int f[2][2] = { {1, 1} , {1, 0} };

	if (n == 0)
	{
		return 0;
	}
	power(f, n);
	std::cout << "\nFibonacci(" << n << ")= " << f[0][0] << "\n";
	return f[0][0];
}
