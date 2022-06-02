#include <iostream>
#include <vector>
int add(int x, int y)
{
	return x + y;
}

int factorial(int x)
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

std::vector<int> fibonacci_series(int n)
{
	// 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, ��..
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
