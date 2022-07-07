#include "UtilityHeader.h"
#include "Integer.h"
#include "Template.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <typeinfo>
#include <string>

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
namespace PerfectForwarding {
	/*
	Note: try it with template and without template. It gives different result!
	I couldn't pass underlying data into the constructor. Why?
	* calling by value calls underlying parametrized constructor
	* calling by creating object calls underlying copy constructor
	* calling by variable name calls underlying copy constructor

	Solution? perfect forwarding. "std::forward"
	* calls underlying move constructor as long as variable is r-value
	*** Take advantage of perfect forwarding function templates is invoking some other function template internally and you want to preserve the information about the types ***
	R-value?
	* doesn't have a variable name
	* just a value exp: 3210, "Mustafa"
	* * if information about type is lost in some process(passing as argument)
	*/
	class Employee {
	private:
		std::string name;
		Integer id;
	public:
		Employee() = default;
		//Employee(const std::string& name, const Integer& id)
		//	: name{ name }, id{ id }
		//{
		//	// copy constructor
		//	log_function_detail("Employee(const std::string& name, const Integer& id) : name{ name }, id{ id }");
		//}
		//Employee(std::string&& name, Integer&& id)
		//	: name{ name }, 
		// id{ std::move(id) } // I am forcing to call move constructor
		//{
		//	// move constructor
		//	log_function_detail("Employee(std::string&& name, Integer&& id) : name{ name }, id{ id }");
		//}

		template<typename T1, typename T2>
		Employee(const T1& name, const T2& id)
			: name{ name }, id{ id }
		{
			// copy constructor
			log_function_detail("Employee(const std::string& name, const Integer& id) : name{ name }, id{ id }");
		}

		template<>
		Employee(const std::string& name, const Integer& id)
			: name{ name },
			id{ id }  // I am forcing to call move constructor
		{
			// copy constructor
			log_function_detail("Employee(std::string&& name, Integer&& id) : name{ name }, id{ id }");
		}

		//template<typename T1, typename T2>
		//Employee(T1&& name, T2&& id)
		//	: name{ name }, id{ id }
		//{
		//	// doesn't preserve underlying type data // calls "Integer(const Integer& obj)"
		//	// templates calls parameterized constructor directly instead of "Integer move constructor"
		//	// move constructor
		//	log_function_detail("Employee(std::string&& name, Integer&& id) : name{ name }, id{ id }");
		//}

		template<typename T1, typename T2>
		Employee(T1&& name, T2&& id)
			: name{ std::forward<T1>(name) }, id{ std::forward<T2>(id) }
		{
			//preserve underlying type data // calls "Integer(Integer&& obj)" as long as variable is r-value
			//templates calls parameterized constructor directly instead of "Integer move constructor"
			//move constructor
			log_function_detail("Employee(std::string&& name, Integer&& id) : name{ name }, id{ id }");
		}

		template<>
		Employee(std::string&& name, Integer&& id)
			: name{ name },
			id{ std::move(id) }  // I am forcing to call move constructor
		{
			// move constructor
			log_function_detail("Employee(std::string&& name, Integer&& id) : name{ name }, id{ id }");
		}

		~Employee() {
			//log_function_detail("~Employee()");
		}
	};

	// factory method
	template<typename T1, typename T2>
	Employee* CreateEmployee(T1&& name, T2&& id) {
		//return new Employee(name, id); // "Integer(const Integer& obj)"
		return new Employee(std::forward<T1>(name), std::forward<T2>(id)); // "Integer(Integer&& obj)"
	}

	void PerfectForwarding_Main() {
		Employee emp1{ "Mustafa", 3210 }; // r-value
		Employee emp11{ "Mustafa", Integer{3210} }; // r-value Integer(doesn't have a name)
		std::string name = "Selcuk";
		Integer val{ 10 };
		Employee emp2{ name, 9876 };
		Employee emp3{ "Mustafa", val };
		Employee emp33{ std::string{"Mustafa"}, val }; // l-value Integer
		Employee emp4{ name, val }; // l-value Integer

		auto emp = CreateEmployee("Mustafa", Integer{ 3210 });

	}
}

namespace variadicTemplates {
	/*
	*** compile time variadic parameter packs ***
	* There is a runtime variadic parameter mechanism inside legacy c-language but it not good as c++ compile-time variadic templates
	* c++ compile-time variadic templates based on recursion so that we need something to finalize the recursion. It is an other function with the same name(base case)+
	* In each recursive call "number of arguments" reduced by one. after the last argument, empty(base-case) function will be called.
	to understand that. look to the "call stack"
	1. Print(1, 2, 3.5, '4')
	2. Print(2, 3.5, '4')
	3. Print(3.5, '4')
	4. Print('4')
	5. Print()   -->> base-case ends recursion
	*/

	template<typename T>
	void Print(std::initializer_list<T> args)
	{
		// accepts only one type arguments
		// Print({ 1,2,3.5,'4' }); // !!! ERROR !!! //It will fail argument deduction
		for (auto&& arg : args)
		{
			std::cout << arg << " ";
		}
		std::cout << '\n';
	}

	// base-case ends recursion
	void Print() {
		//std::cout << '\n' << ','; // to remove extra "," check with sizeof...()
		std::cout << '\n';
	}

	// template parameter pack. It will be automatically expanded by the compiler. It will excepts any number of arguments. It is like a "c# params" keyword
	// You have to rely on the recursion
	template<typename T, typename... Parameters>
	void Print(T a, Parameters... args) {
		//std::cout << sizeof...(Parameters);
		//std::cout << sizeof...(args);
		std::cout << a;
		if (sizeof...(args) != 0) {
			std::cout << ',';
		}

		// call at the end of function
		//Print(args...); // runtime-stack-overflow without base-case function and second argument
		Print(std::forward<Parameters>(args)...); // runtime-stack-overflow without base-case function and second argument // perfect forwarding
	}

	void variadicTemplates_Main() {
		Print({ 1,2,3,4 });
		// Print({ 1,2,3.5,'4' }); // !!! ERROR !!! //It will fail argument deduction
		Print(1, 2, 3.5, '4', Integer{ 506 }); // use perfect forwarding to move


	}
}
namespace classTemplates {
	void classTemplates_Main() {

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
	template<size_t arrSize>
	const char& max(const char(&pArr)[arrSize]) {
		size_t idx = 0;
		const char temp = pArr[idx];
		const char maxValue = temp;
		for (idx += 0; idx < arrSize; idx++) {
			temp = pArr[idx];
			if (std::strcmp(maxValue, temp) < 0) {
				// new value bigger than old maximum
				maxValue = temp;
			}
		}
		return maxValue;
	}
	template<size_t arrSize>
	const char* max(const char(*pArr)[arrSize]) {
		size_t idx = 0;
		const char temp = *pArr[idx];
		const char maxValue = temp;
		for (idx += 0; idx < arrSize; idx++) {
			temp = *pArr[idx];
			if (std::strcmp(maxValue, temp) < 0) {
				// new value bigger than old maximum
				maxValue = temp;
			}
		}
		return maxValue;
	}
	template<size_t arrSize>
	std::string& max(std::string(&pArr)[arrSize]) {
		size_t idx = 0;
		std::string temp = pArr[idx];
		std::string maxValue = temp;
		for (idx += 0; idx < arrSize; idx++) {
			temp = *pArr[idx];
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
	template<size_t arrSize>
	const char& min(const char(&pArr)[arrSize]) {
		size_t idx = 0;
		const char temp = pArr[idx];
		const char minValue = temp;
		for (idx += 0; idx < arrSize; idx++) {
			temp = pArr[idx];
			if (std::strcmp(minValue, temp) > 0) {
				// new value bigger than old maximum
				minValue = temp;
			}
		}
		return minValue;
	}
	template<size_t arrSize>
	const char* min(const char(*pArr)[arrSize]) {
		size_t idx = 0;
		const char temp = *pArr[idx];
		const char minValue = temp;
		for (idx += 0; idx < arrSize; idx++) {
			temp = *pArr[idx];
			if (std::strcmp(minValue, temp) > 0) {
				// new value bigger than old maximum
				minValue = temp;
			}
		}
		return minValue;
	}
	template<size_t arrSize>
	std::string& min(std::string(&pArr)[arrSize]) {
		size_t idx = 0;
		std::string temp = pArr[idx];
		std::string minValue = temp;
		for (idx += 0; idx < arrSize; idx++) {
			temp = pArr[idx];
			if (minValue > temp) {
				// new value bigger than old maximum
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
	template<size_t arrSize>
	std::pair<const char&, const char&> MinMax(const char(&pArr)[arrSize]) {
		size_t idx = 0;
		const char temp = pArr[idx];
		const char maxValue = temp;
		const char minValue = temp;
		for (idx += 0; idx < arrSize; idx++) {
			temp = pArr[idx];
			if (std::strcmp(maxValue, temp) < 0) {
				// new value bigger than old maximum
				maxValue = temp;
			}
			else if (std::strcmp(minValue, temp) > 0) {
				// new value bigger than old maximum
				minValue = temp;
			}
		}
		return std::pair<const char*, const char*>(minValue, maxValue);
	}
	template<size_t arrSize>
	std::pair<const char*, const char*> MinMax(const char(*pArr)[arrSize]) {
		size_t idx = 0;
		const char temp = *pArr[idx];
		const char maxValue = temp;
		const char minValue = temp;
		for (idx += 0; idx < arrSize; idx++) {
			temp = *pArr[idx];
			if (std::strcmp(maxValue, temp) < 0) {
				// new value bigger than old maximum
				maxValue = temp;
			}
			else if (std::strcmp(minValue, temp) > 0) {
				// new value bigger than old maximum
				minValue = temp;
			}
		}
		return std::pair<const char*, const char*>(minValue, maxValue);
	}
	template<size_t arrSize>
	std::pair<std::string&, std::string&> MinMax(std::string(&pArr)[arrSize]) {
		size_t idx = 0;
		std::string temp = pArr[idx];
		std::string maxValue = temp;
		std::string minValue = temp;
		for (idx += 0; idx < arrSize; idx++) {
			temp = pArr[idx];
			if (maxValue < temp) {
				// new value bigger than old maximum
				maxValue = temp;
			}
			else if (minValue > temp) {
				// new value bigger than old maximum
				minValue = temp;
			}
		}
		return std::pair<const char*, const char*>(minValue, maxValue);
	}

	void Assignment1_Test() {
		int x = 1, y = 2;
		std::cout << "R(T Add(T x, T y)): " << Add(x, y) << '\n';

		// generate bunch of numbers
		std::random_device rndDev;
		std::default_random_engine engine(rndDev());
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
	void Assignment3_Test() {
		/*
		Create a factory that creates an instance of some type T, initializes it with arguments and returns it.

		Here are some usage examples of the factory.

		int *p1 = CreateObject<int>(5) ;

		std::string *s = CreateObject<std::string>() ;//Default construction

		Employee * emp = CreateObject<Employee>(
		"Bob",    //Name
		101,      //Id
		1000) ;   //Salary

		Contact *p = CreateObject<Contact>(
		"Joey",                //Name
		987654321,             //Phone number
		"Boulevard Road, Sgr", //Address
		"joey@poash.com") ;    //Email

		*/
	}
	void Assignment_Tests_subroutine() {
		Assignment1_Test();
		Assignment2_Test();
		Assignment3_Test();

	}
}

void Template_Main() {
	//Template::Template1_Subroutine();
	//Template::Template2_Subroutine();
	//PerfectForwarding::PerfectForwarding_Main();
	variadicTemplates::variadicTemplates_Main();
	classTemplates::classTemplates_Main();
	//Assignment::Assignment_Tests_subroutine();
}