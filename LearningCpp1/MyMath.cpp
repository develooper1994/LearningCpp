#include <iostream>
#include <vector>
#include <cmath>

#include <algorithm>
#include <random>

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
	// 0, 1, 2, 3, 4, 5, 6,  7,  8,  9, 10, 11,  12, ……..
	// 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, ……..
	auto temp1 = 0; // first index= 0
	auto temp2 = 1; // second index= 1
	auto next = 0; // 
	std::vector<int> vec{ 0, 1 };
	auto& result = vec; // store the result and quit whenever i want.
	if (n < 0)
	{
		n = abs((int)n);
	}
	if (n == 0)
		vec.pop_back();
	result = vec; // don't quit now.

	auto fibonacci_generator = [&n, &temp1, &temp2, &next, &vec]() {
		for (size_t i = 2; i < n; ++i)
		{
			next = temp1 + temp2;
			temp1 = temp2;
			temp2 = next;
			vec.push_back(next);
		}
	};
	fibonacci_generator();

	auto fibonacci_print = [&n, &vec](const int& line_max = 15) {
		if ((n >= 0)) std::cout << 0 << ", ";
		if ((n >= 1)) std::cout << 1 << ", ";
		for (size_t i = 2; i < n; ++i)
		{
			if ((i % line_max + 1) == line_max)
			{
				// enter the new line
				std::cout << '\n';
			}
			std::cout << vec.at(i) << ", ";
		}

	};
	fibonacci_print(15);

	return result; // quit end of the function.
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


namespace HomeWork1 {
	int LinearSearch(const std::vector<int>& vec, int item) {
		// find item return first index
		int size = vec.size();
		for (int i = 0; i < size; i++)
		{
			if (vec.at(i) == item)
			{
				std::cout << "buldu";
				return i;
			}
		}
		std::cout << "bulamadý";
		return -1;
	}

	std::vector<float> MovingAverage(const std::vector<int>& vec, int block_size) {
		// y[n] = (1/N) * sum(x[n-i]); i=0->N-1
		// extremely simple implementation. There is severely implementations.
		// normally i need a ring-buffer. I will make other Moving Average filters later.
		int size = vec.size();
		float temp{ 0 };
		float avg{ 0 };
		std::vector<float> avg_vec{};
		for (auto&& i = 0; i < size - block_size; ++i)
		{
			temp = 0;
			for (size_t j = i; j < block_size + i; ++j)
			{
				temp += vec.at(i);
			}
			avg = temp / block_size;
			avg_vec.push_back(avg);
		}
		return avg_vec;
	}

	int custom_abs(const int& x) {
		return x >= 0 ? x : x * -1;
	}

	void homework1_test() {
		// std::srand(std::time(nullptr)); // old time based random seed. Not recommended due to security reasons(like timing attacks). 
		// Modern way recommends random_device
		// std::random_device rnd_dev;										// random device
		//std::mt19937 engine{ rnd_dev() };									// select engine
		std::default_random_engine engine;									// or just use STL engine
		std::uniform_int_distribution<int> distribution(1, 10);				// determine the range
		auto generator = [&distribution, &engine]()			// define the generator
		{
			return distribution(engine);
		};

		std::vector<int> vec(10);											// reserve 10 elements
		std::generate(vec.begin(), vec.end(), generator);	// generate the randoms
		//std::shuffle(begin(vec), end(vec), engine);						// rearrange the elements of a range in random order.


		std::cout << "\n\Linear Search test\n";
		auto index = LinearSearch(vec, 5);
		std::cout << "index= " << index << '\n';


		std::cout << "\n\Moving Average test\n";
		int block_size = 3;
		auto result = MovingAverage(vec, block_size);
		for (auto&& ptr = result.begin(); ptr < result.end(); ++ptr)
		{
			std::cout << "i: " << *ptr << '\n';
		}


		std::cout << "\n\tcustom_abs test\n";
		int x = 10;
		std::cout << "x = " << x << " || " << "custom_abs(x) = " << custom_abs(x) << '\n';
		x = 0;
		std::cout << "x = " << x << " || " << "custom_abs(x) = " << custom_abs(x) << '\n';
		x = -10;
		std::cout << "x = " << x << " || " << "custom_abs(x) = " << custom_abs(x) << '\n';
	}
}