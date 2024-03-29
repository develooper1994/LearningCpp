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
	int add(int x = 0, int y = 0) {
		return x + y;
	}
	int substract(int x, int y) {
		return x - y;
	}
}
int add(const int& x, const int& y) {
	return x + y;
}
float add(float x, float y) {
	return x + y;
}
float add(float x, int y) {
	return float(x + y);
}

size_t factorial(uint32_t x) {
	if (x < 0) {
		std::cerr << "Error! Factorial of a negative number doesn't exist.";
		return -1;
	}
	size_t temp = 1;
	for (size_t i = 1; i <= x; ++i)
		temp *= i;

	return temp;
}
size_t factorial_rec(uint32_t x) {
	if (x < 1) {
		return 1; // factorial_rec(0)
	}
	return x * factorial_rec(x - 1);
	//factorial_rec(7);
	// 7 * factorial_rec(6);
	// 6 * factorial_rec(5);
	// 5 * factorial_rec(4);
	// 4 * factorial_rec(3);
	// 3 * factorial_rec(2);
	// 2 * factorial_rec(1);
	// 1 * factorial_rec(0);
}

std::vector<int> fibonacci_series(uint32_t n) {
	// 0, 1, 2, 3, 4, 5, 6,  7,  8,  9, 10, 11,  12, ……..
	// 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, ……..
	auto temp1 = 0; // first index= 0
	auto temp2 = 1; // second index= 1
	auto next = 0; // 
	std::vector<int> vec{ 0, 1 };
	if (n < 0)
		n = abs((int)n);
	else if (n == 0)
		vec.pop_back();
	auto& result = vec; // don't quit now. // store the result and quit whenever i want.

	auto fibonacci_generator = [&n, &temp1, &temp2, &next, &vec]() {
		for (size_t i = 2; i < n; ++i) {
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
		for (size_t i = 2; i < n; ++i) {
			if ((i % line_max + 1) == line_max) {
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
void multiply(int F[2][2]) {
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
void power(int F[2][2], int n) {
	// optimized(halving method)
	if (n == 0 || n == 1) {
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
int fib_power(int n) {
	int f[2][2] = { {1, 1} , {1, 0} };

	if (n == 0) {
		return 0;
	}
	power(f, n);
	std::cout << "\nFibonacci(" << n << ")= " << f[0][0] << "\n";
	return f[0][0];
}


namespace HomeWork1 {
	size_t LinearSearch(const std::vector<int>& vec, int item) {
		// find item return first index
		size_t size = vec.size();
		for (size_t i = 0; i < size; i++) {
			if (vec.at(i) == item) {
				std::cout << "buldu";
				return i;
			}
		}
		std::cout << "bulamadư";
		return -1;
	}

	std::vector<float> MovingAverage(const std::vector<int>& vec, size_t block_size) {
		// y[n] = (1/N) * sum(x[n-i]); i=0->N-1
		// extremely simple implementation. There is severely implementations.
		// normally i need a ring-buffer. I will make other Moving Average filters later.
		size_t size = vec.size();
		float temp{ 0 };
		float avg{ 0 };
		std::vector<float> avg_vec{};
		for (size_t i = 0; i < size - block_size; ++i) {
			temp = 0;
			for (size_t j = i; j < block_size + i; ++j) {
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
		std::random_device rnd_dev;										// random device
		//std::mt19937 engine{ rnd_dev() };									// select engine
		std::default_random_engine engine(rnd_dev());						// or just use STL engine
		std::uniform_int_distribution<int> distribution(1, 10);				// determine the range
		auto generator = [&distribution, &engine, &rnd_dev]()			// define the generator
		{
			engine.seed(rnd_dev());
			return distribution(engine);
		};

		std::vector<int> vec(10);											// reserve 10 elements
		std::generate(vec.begin(), vec.end(), generator);	// generate the randoms
		//std::shuffle(begin(vec), end(vec), engine);						// rearrange the elements of a range in random order.


		std::cout << "\nLinear Search test\n";
		auto index = LinearSearch(vec, 5);
		std::cout << "index= " << index << '\n';


		std::cout << "\nMoving Average test\n";
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



// I like it :)
std::string stringSum(std::string a, std::string b) {
	/*
	* Sum of really big integers
	* reference: https://stackoverflow.com/questions/42357976/how-to-get-the-sum-of-two-strings-of-numbers-c
	TEST:
		string result = doSum("1234567890", "123789456123");
		cout << result << "\n";

	Small Integers:
	// use standard library
	std::string num1 = "12";
	std::string num2 = "4";
	std::string sum = std::to_string(std::stoi(num1) + std::stoi(num2));
	*/
	if (a.size() < b.size())
		std::swap(a, b);

	size_t i = b.size() - 1;
	size_t j = a.size() - 1;
	for (; i >= 0; i--, j--)
		a[j] += (b[i] - '0');

	for (size_t i = a.size() - 1; i > 0; i--) {
		if (a[i] > '9') {
			int d = a[i] - '0';
			a[i - 1] = ((a[i - 1] - '0') + d / 10) + '0';
			a[i] = (d % 10) + '0';
		}
	}

	if (a[0] > '9') {
		std::string k;
		k += a[0];
		a[0] = ((a[0] - '0') % 10) + '0';
		k[0] = ((k[0] - '0') / 10) + '0';
		a = k + a;
	}
	return a;
}
