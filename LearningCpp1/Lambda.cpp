#include "Lambda.h"
#include <fstream>

/*
* NOTE: It is like a function pointers but i can threat them as a objects. Lambda functions and function pointers are useful as callback functions.
* Note(function pointer): function pointers called from address. It cannot be optimized(cannot be inlined) by the compiler.
* * Also cannot have a state. It is a global function call. For example, cannot count how many comparisons have been made.

* Note(function objects - struct or class "operator()()" overloaded): It is a syntactic sugar! It is a member function call so that I can store a state inside struct
* * compiler can inline it during optimization

* Note(Lambda Expression): It is a syntactic shortcut for function object.
* * Defines an anonymous function object
* * Can be passed as an argument
* * Can accept parameters and return values
* * [<&capture by reference>, <=capture by copy>](<args>)<mutable><exception specifier> -> <return type>
	{
		<function body>
	}
***Generalized Capture(c++14):
[var=expression](args)
[&var=expression](args)

*** I can call in "C" functions. If parameter and capture list is empty lambda composes as function pointer. Automatic lambda function to function pointer conversion.
*
*/

/*
		Function Pointer						Function Object(recommended for old language standard)
	* Invoked through a pointer				* Invoked through an object
	* Dynamic in nature						* Static in nature
	* Can be specified at runtime			* Must be specified at compile time
	* Difficult to optimize					* Easy to optimize
	* Slow									* Fast
	* Cannot store state					* Can store state
*/

namespace LambdaUtils {
	template<typename T, int size>
	void Sort(T(&arr)[size]) {
		auto length = size - 1;
		for (size_t i = 0; i < length; i++) {
			for (size_t j = 0; j < length; j++) {
				//if (arr[j] > arr[j + 1]) {
				if (arr[j] > arr[j + 1]) {
					std::swap((arr[j]), (arr[j + 1]));
				}
			}
		}
	}

	using Comparator = bool(*)(int, int); // predicate is a function that returns a boolean value.
	template<typename T, int size,
		typename Comparator> // I can now use function object.
	void Sort(T(&arr)[size], Comparator comp) {
		auto length = size - 1;
		for (size_t i = 0; i < length; i++) {
			for (size_t j = 0; j < length; j++) {
				//if (arr[j] > arr[j + 1]) {
				if (comp(arr[j], arr[j + 1])) {
					std::swap((arr[j]), (arr[j + 1]));
				}
			}
		}
	}
	bool Comp_descending(int x, int y) {
		return x > y;
	}
	bool Comp_ascending(int x, int y) {
		return x < y;
	}
	struct Comp {
		bool operator()(int x, int y) {
			return Comp_descending(x, y);
		}
	};

	template<typename T, int size, typename CallBack>
	void ForEach(T(&arr)[size], CallBack operation) {
		for (size_t i = 0; i < size - 1; ++i) {
			operation(arr[i]);
		}
	}
}

namespace Function_Pointer_Function_Object {

	void Function_Pointer_Function_Object_subroutine1() {
		std::cout << "\n-*-*-*-*-* Function_Pointer_Function_Object_subroutine1 *-*-*-*-*\n";
		int arr[]{ 1, 6, 8, 4, 0 };
		// function pointer
		{
			std::cout << "arr: ";
			for (const auto& i : arr)
				std::cout << i << ' ';
			std::cout << '\n';
			//LambdaUtils::Sort(arr, LambdaUtils::Comp_descending);
			//LambdaUtils::Sort(arr, LambdaUtils::Comp_ascending);
		}

		// function object
		{
			LambdaUtils::Comp comp;
			std::cout << "\nfunction object: " << std::boolalpha << comp(3, 5) << '\n'; // comp.operator()(3,5)
			Sort(arr, comp);
			std::cout << "arr: ";
			for (const auto& i : arr)
				std::cout << i << ' ';
			std::cout << '\n';
		}

	}
}

namespace Lambda {
	template<typename T>
	class SumClass {
	public:
		T operator()(T x, T y) const {
			return x + y;
		}
	};
	void Lambda_subroutine1() {
		std::cout << "\n-*-*-*-*-* Lambda_subroutine1 *-*-*-*-*\n";
		[]() {
			std::cout << "\nEverybody be quiet! Lambda talks...\n";
		}();

		auto add_some = [](int x, int y) -> int {return x + y; }; // return type is optional most of the time.
		std::cout << add_some(3, 5) << '\n';
		std::cout << typeid(add_some).name() << '\n'; // It is internally is a class. void __cdecl Lambda::Lambda_subroutine1(void)'::`2'::<lambda_2>

		SumClass<int> add_some_class;
		std::cout << add_some_class(3, 5) << '\n';
		std::cout << typeid(add_some_class).name() << '\n'; // It is internally is a class. void __cdecl Lambda::Lambda_subroutine1(void)'::`2'::<lambda_2>
	}

	template<typename T>
	struct __accumulate {
		// how lambda perform operations
		// capture list
		int offset;
		// constructor
		__accumulate(int off) : offset{ off } {}
		// lambda function call
		void operator()(T& x) const /*lambda mutable*/
		{
			x += offset;
			//++offset; // promised not to change
		}
	};
	void Lambda_subroutine2() {
		std::cout << "\n-*-*-*-*-* Lambda_subroutine2 *-*-*-*-*\n";
		int arr[]{ 1, 6, 8, 4, 0 };
		std::cout << "arr: ";
		for (const auto& i : arr)
			std::cout << i << ' ';
		std::cout << '\n';

		auto comp = [](int x, int y) {return x > y; };
		LambdaUtils::Sort(arr, comp);

		std::cout << "arr: ";
		for (const auto& i : arr)
			std::cout << i << ' ';
		std::cout << '\n';

		// LAMBDA DETAILS
		__accumulate<int> acc(3);
		int x = 5;
		acc(x);

		int offset = 5; // we need to explicitly capture this variable, so that it get accessible inside the lambda expression, 
		LambdaUtils::ForEach(arr,
			[offset] /* It is not a reference capture. It has different address than outside of the lambda. It is const by default */
		(auto& x) mutable /* to remove const capture by value */
			{
				x += offset;
				++offset;
			});
		auto sum = 0; // we need to explicitly capture this variable, so that it get accessible inside the lambda expression, 
		LambdaUtils::ForEach(arr,
			//	[&sum] // capture variable by reference
			[&] // capture all by reference
		//[=] // capture all by value
		//[=,&sum] // capture all by value except that capture sum by reference
		//[&, sum] // capture all by reference except that capture sum by value
		//[this] // capture this(all member variables)
		(auto& x)
			{
				sum += x;
			});
		std::cout << "\nsum: " << sum << '\n';
		LambdaUtils::ForEach(arr,
			[](int x) {
				std::cout << x << ' ';
			});
	}

	class Product {
		std::string name;
		float price;
	public:
		Product(const std::string& _name, float _price)
			: name(_name), price(_price)
		{}
		void AssignFinalPrice() {
			float taxes[]{ 12,5,5 };
			float basePrice{ price };
			std::for_each(std::begin(taxes), std::end(taxes),
				[basePrice, this](float tax) {
					float taxedPrice = basePrice * tax / 100;
					price += taxedPrice;
				});
		}
		float GetPrice()const {
			return price;
		}
	};
	void Lambda_subroutine3() {
		std::cout << "\n-*-*-*-*-* Lambda_subroutine3 *-*-*-*-*\n";
		int i = 3;
		atexit(
			// [i] // !!! ERROR !!!
			[]
		() {
				std::cout << "Program is exiting...\n";
			}); // I can call in "C" functions. If parameter and capture list is empty lambda composes as function pointer. Automatic lambda function to function pointer conversion.

		Product p{ "Watch", 500 };
		p.AssignFinalPrice();
		std::cout << p.GetPrice() << '\n';

		std::cout << "an extreme lambda call :D\n";
		int var = 5;
		[](int x) {
			x *= 2;
			[](int x) {
				std::cout << x << '\n';
			}(x);
		}(var);

	}

	void GeneralizedCapture() {
		// c++14 feature
		std::cout << "\n-*-*-*-*-* GeneralizedCapture *-*-*-*-*\n";
		int x{ 1 };
		auto fn = [y = x] // created a new variable "y"
		(int arg) {
			return y + arg;
		};
		std::cout << fn(4) << '\n';

		std::ofstream out{ "GeneralizedCapture.txt" }; // non-copyable object
		auto write = [out = std::move(out)] // created a new reference "out". I couldn't use "out" after the lambda expression
		(int x) mutable {
			out << x;
		};

		write(200);

	}
}

namespace Assignment {
	/*
	* T Max(T, T); //Return largest element
	* bool Greater(T, T) ; //Return true if first argument is greater than the second
	* bool Less(T, T) ; //Return true if first argument is less than the second
	* pair<T,T> MinMax(ItrBegin, ItrEnd) ;//Accept iterators of any container and return the largest and smallest element from that container.
	*/
	template<typename T>
	T Max(T x, T y) {
		if (x > y) {
			return x;
		}
		else if (y > x) {
			return y;
		}
	}
	template<typename T>
	bool Greater(T x, T y) {
		return x > y;
	}
	template<typename T>
	bool Less(T x, T y) {
		return x < y;
	}
	template<typename T>
	std::pair<T, T> MinMax(T IterBegin, T IterEnd) {
		if (IterBegin == IterEnd) throw std::logic_error("!!! logic_error !!!");

		T smallest = IterBegin;
		T biggest = IterBegin;
		for (T i = ++IterBegin; i < IterEnd; ++i) {
			auto elem = i;
			if (*smallest > *elem)
				smallest = elem;
			else if (*biggest < *elem)
				biggest = elem;
		}
		std::pair<T, T> result;
		result.first = smallest;
		result.second = biggest;
		return result;
	}
	void Assignement_Main() {
		std::cout << "\n-*-*-*-*-* Assignement_Main *-*-*-*-*\n";
		int arr[]{ 1,4,5,6,7,3,2 };
		auto x = arr[2]; // 5
		auto y = arr[4]; // 7
		std::cout << "\nMax: " << Max(x, y) << '\n';
		std::cout << "\Greater: " << Greater(x, y) << '\n';
		std::cout << "\Less: " << Less(x, y) << '\n';
		auto result = MinMax(std::begin(arr), std::end(arr));
		std::cout
			<< "\MinMax.min: " << *result.first << " || "
			<< "\MinMax.max: " << *result.second;
	}
}

void Lambda_Main() {
	Function_Pointer_Function_Object::Function_Pointer_Function_Object_subroutine1();
	Lambda::Lambda_subroutine1();
	Lambda::Lambda_subroutine2();
	Lambda::Lambda_subroutine3();
	Lambda::GeneralizedCapture();
	Assignment::Assignement_Main();
}
