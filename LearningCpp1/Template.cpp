#include "Template.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <typeinfo>

// Also known as meta-programing and generic programing
/*
* Templates calculates at compile-time. Optimizes code significantly
*****
* A template function class only acts
* The compiler generates code from blueprint at compile time.
* It is known as template instantiation
*****
* Full definition of template should be available
* Define in header file
* Otherwise you will receive "bad linker error"
The template instantiation to work, the compiler should be able to see the full definition of the template.
- That is why, function and class templates are always defined in as header file,
- Templates generally do not use the conventional style of declaration and definition.
- NOTE: also template is outside of the function
*****

INSIDE ASSEMBLY:
PUBLIC	??$max@D@Template@@YADDD@Z			; Template::max<char>
PUBLIC	??$max@H@Template@@YAHHH@Z			; Template::max<int>
PUBLIC	??$max@M@Template@@YAMMM@Z			; Template::max<float>
PUBLIC	??$max@N@Template@@YANNN@Z			; Template::max<double>

*/
namespace Template {
	//// I have to write an overload for each type
	//int max(int x, int y) {
	//	return x > y ? x : y;
	//}
	//float max(float x, float y) {
	//	return x > y ? x : y;
	//}

	// I can write only once. Compiler generates rest of type when we use it. Also compiler can deduce type and generates function body.
	// template<class type> // also works in this context. The difference between "class" and "typename" are apparent only when you do "advanced template programing"
	// The template type can be used as return type
	template<typename T>
	T max(T x, T y) {
		std::cout << typeid(T).name() << '\n';
		return x > y ? x : y;
	}

	// Explicit Specialization
	/*
	* Template specialized for a particular type
	* Provides correct semantics for some data type
	* Or implement an algorithm optimally for a specific type
	* Explicitly specialized functions must be defined in a .cpp file
	* Primary template definition should occur before specialization
	*
	* recommended and optionally: Also specify the type for which you are specializing.
	*/
	template<> const char* max<const char*> // recommended and optional
	(const char* x, const char* y) {
		// auto s = max(a, b); // not to compares addresses. specialize
		std::cout << "R(template<> const char* max(const char* x, const char* y))\n";
		return strcmp(x, y) > 0 ? x : y;
	}

	// Explicit Instantiation for specific type
	template char max(char x, char y);

	// generic template function pointer
	template<typename T>
	T(*pfn)(T, T) = max;

	// generic template function reference
	template<typename T>
	T(&rfn)(T, T) = max;

	void Template1_Subroutine() {
		// asm output: ??$max@H@Template@@YAHHH@Z			; Template::max<int>
		//auto num2 = max<int>(3, 4); // explicit
		auto num1 = max(3, 4); // implicit
		std::cout << "num: " << num1 << '\n';

		// asm output: PUBLIC	??$max@M@Template@@YAMMM@Z			; Template::max<float>
		//auto num1 = max<float>(3.3f, 4.4f); // explicit
		auto num2 = max(3.3f, 4.4f); // implicit. 
		std::cout << "num: " << num2 << '\n';

		//auto num3 = max(3, 4.4f); // !!! ERROR !!! // (T x) != (T y)
		auto num3 = max(static_cast<float>(3), 4.4f); // only way to compile for one <typename T> without explicit!
		std::cout << "num: " << num3 << '\n';

		auto num4 = max<double>(3, 4.4f); // only way to compile for one <typename T> without explicit!
		std::cout << "num: " << num4 << '\n';

		// template function pointer - Compiler now generates function body for max<int>
		int(*pfn)(int, int) = max;
		// template function reference
		int(&rfn)(int, int) = max;

		// adress ve value with templates
		const char* b{ "B" };
		const char* a{ "A" };
		auto s = max(a, b); // compares addresses
		//auto s = max(*a, *b); // compares values
		std::cout << s << '\n';
	}
	// Non-type template
	/*
	* Expression that is computed at compile time within a  template argument list
	* Must be a constant expression (addresses, references, integrals, nullptr, enums)
	* Part of the template type
	* Used by std::begin & std::end
	*/
	// NOTE: size is a constant that compile-time calculated
	template<int size> // <int size = 5> // also works
	void Print() {
		//size++; // !!! ERROR !!!
		std::cout << size << '\n';
	}
	template <typename T>
	T Sum(T* parr, int size) {
		T sum{};
		for (size_t idx = 0; idx < size; idx++) {
			sum += parr[idx];
		}
		return sum;
	}
	// NOTE: size is a constant that compile-time calculated. 
	// *** I can take advantage of "compile-time constant calculation" to "calculate my array size" ***
	template <typename T, int size>
	T Sum(T(&parr)[size]) {
		T sum{};
		for (size_t idx = 0; idx < size; idx++) {
			sum += parr[idx];
		}
		return sum;
	}
	void Template2_Subroutine()
	{
		Print<5>();	// ! WORKS !
		int i = 3;	// !!! ERROR !!! i is runtime variable
		//Print<i>();	// !!! ERROR !!! i is runtime variable
		Print<sizeof(i)>(); // ! WORKS ! sizeof(i) calculated at compile-time
		const int i2 = 3;	// ! WORKS ! i is runtime variable
		//constexpr int i2 = 3;	// ! WORKS ! i is runtime variable
		Print<i2>();

		// Sum1
		int arr[]{ 1,4,6,8,0 }; // size==5
		int(&ref)[5] = arr; // I have to specify "arr size" because it is constant.
		auto iterator_begin = std::begin(arr);
		int sum = Sum(arr, 4);
		std::cout << "Sum1: " << sum << '\n';

		// I can pass an array into function without explicitly specifying the size. 
		// This is used by the standard library to implement the global functions, std::begin() and std::end() for array
		sum = Sum(arr);
		std::cout << "Sum1: " << sum << '\n';

	}

}

namespace Assignment {
	// -*-*-* Add *-*-*-
	template<typename T>
	T Add(T x, T y) {
		return x + y;
	}
	template<>
	const char* Add<const char*> // recommended and optional
		(const char* x, const char* y) {
		auto combined = std::string(x) + std::string(y);
		return combined.c_str();
	}
	template<>
	std::string Add<std::string> // recommended and optional
		(std::string x, std::string y) {
		auto combined = std::string(x) + std::string(y);
		return combined;
	}

	// -*-*-* ArraySum *-*-*-
	template<typename T>
	T ArraySum(const T* pArr, const size_t& arrSize) {
		T sum = 0;
		for (size_t idx = 0; idx < arrSize; idx++) {
			sum += *(pArr + idx);
		}
		return sum;
	}
	template<typename T, size_t arrSize>
	T ArraySum(T(&pArr)[arrSize]) {
		T sum = 0;
		for (size_t idx = 0; idx < arrSize; ++idx) {
			sum += pArr[idx];
		}
		return sum;
	}

	// -*-*-* max *-*-*-
	template<typename T>
	T max(const T* pArr, const size_t& arrSize) {
		size_t idx = 0;
		T temp = pArr[idx];
		T maxValue = temp;
		for (idx += 0; idx < arrSize; idx++) {
			temp = pArr[idx];
			if (maxValue < temp) {
				// new value bigger than old maximum
				maxValue = temp;
			}
		}
		return maxValue;
	}
	template<typename T, size_t arrSize>
	T max(T(&pArr)[arrSize]) {
		size_t idx = 0;
		T temp = pArr[idx];
		T maxValue = temp;
		for (idx += 0; idx < arrSize; idx++) {
			temp = pArr[idx];
			if (maxValue < temp) {
				// new value bigger than old maximum
				maxValue = temp;
			}
		}
		return maxValue;
	}

	// -*-*-* min *-*-*-
	template<typename T>
	T min(const T* pArr, const size_t& arrSize) {
		size_t idx = 0;
		T temp = pArr[idx];
		T minValue = temp;
		for (idx += 0; idx < arrSize; idx++) {
			temp = pArr[idx];
			if (minValue > temp) {
				// new value smaller than old minimum
				minValue = temp;
			}
		}
		return minValue;
	}
	template<typename T, size_t arrSize>
	T min(T(&pArr)[arrSize]) {
		size_t idx = 0;
		T temp = pArr[idx];
		T minValue = temp;
		for (idx += 0; idx < arrSize; idx++) {
			temp = pArr[idx];
			if (minValue > temp) {
				// new value smaller than old minimum
				minValue = temp;
			}
		}
		return minValue;
	}

	// -*-*-* MinMax *-*-*-
	template<typename T>
	std::pair<T, T> MinMax(const T* pArr, const size_t& arrSize) {
		size_t idx = 0;
		T temp = *(pArr + idx);
		T maxValue = temp;
		T minValue = temp;
		for (idx += 0; idx < arrSize; idx++) {
			temp = *(pArr + idx);
			if (maxValue < temp) {
				// new value bigger than old maximum
				maxValue = temp;
			}
			else if (minValue > temp) {
				// new value smaller than old minimum
				minValue = temp;
			}
		}
		return std::pair<T, T>(minValue, maxValue);
	}
	template<typename T, size_t arrSize>
	std::pair<T, T> MinMax(T(&pArr)[arrSize]) {
		size_t idx = 0;
		T temp = pArr[idx];
		T maxValue = temp;
		T minValue = temp;
		for (idx += 0; idx < arrSize; idx++) {
			temp = pArr[idx];
			if (maxValue < temp) {
				// new value bigger than old maximum
				maxValue = temp;
			}
			else if (minValue > temp) {
				// new value smaller than old minimum
				minValue = temp;
			}
		}
		return std::pair<T, T>(minValue, maxValue);
	}

	void Assignment1_Test() {
		int x = 1, y = 2;
		std::cout << "R(T Add(T x, T y)): " << Add(x, y) << '\n';

		// generate bunch of numbers
		std::default_random_engine engine;
		std::uniform_real_distribution distribution(1.0, 10.0);
		auto generator = [&engine, &distribution]() {
			return distribution(engine);
		};

		std::vector<double> vec(10);
		std::generate(vec.begin(), vec.end(), generator);
		auto pArr = vec.data();
		auto arrSize = vec.size();
		std::cout << " Vector: ";
		for (size_t i = 0; i < arrSize; i++) {
			std::cout << vec[i] << ' ';
		}
		std::cout << '\n';

		auto sum = ArraySum(pArr, arrSize);
		std::cout << "R(T ArraySum(const T* pArr, size_t arrSize)): " << sum << '\n';

		auto maxValue = max(pArr, arrSize);
		std::cout << "R(T max(const T* pArr, size_t arrSize)): " << maxValue << '\n';

		auto minValue = min(pArr, arrSize);
		std::cout << "R(T min(const T* pArr, size_t arrSize)): " << minValue << '\n';

		auto MinMaxValue = MinMax(pArr, arrSize);
		std::cout
			<< "R(std::pair<T, T> MinMax(const T* pArr, size_t arrSize)): \n"
			<< "minValue: " << MinMaxValue.first << '\n'
			<< "maxValue: " << MinMaxValue.second << '\n';
	}

	void Assignment2_Test() {

	}
	void Assignment_Tests_subroutine() {
		Assignment1_Test();
	}
}

void Template_Main() {
	Template::Template1_Subroutine();
	Assignment::Assignment_Tests_subroutine();
	Template::Template2_Subroutine();
}