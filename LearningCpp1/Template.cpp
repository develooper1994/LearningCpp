#include "UtilityHeader.h"
#include "Integer.h"
#include "Template.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <string>
#include <typeinfo>
#include <type_traits>

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
			log_function_detail("~Employee()");
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
	// This is much better than using a constant value in Buffer because the template argument is compile-time constant
	template<typename T, size_t Buffer_size = 512>
	class Stack {
	private:
		T Buffer[Buffer_size];
		int top{ -1 };
	public:
		// -*-*-* Constructors *-*-*-
		Stack() = default;
		// Copy Constructor
		// Stack(const Stack<T, Buffer_size>& obj) // not required inside of the class
		Stack(const Stack& obj) {
			top = obj.top;
			for (size_t i = 0; i <= sizeof(obj.Buffer); ++i) { // check until to the top of object that copying is not a good idea in my opinion
				Buffer[i] = obj.Buffer[i];
			}
		}
		Stack(std::initializer_list<int> li) {
			int count = 0;
			for (auto i = li.begin(); i < li.end(); ++i) {
				Buffer[count++] = *i;
			}
		}
		// -*-*-* Methods *-*-*-
		void Push(int element) {
			Buffer[++top] = element;
		}
		void Pop() {
			--top;
		}
		const T& Top() {
			return Buffer[top];
		}
		bool isEmpty() {
			return top == -1;
		}
		// factory method

		//static Stack Create() {
		//	// short-hand notion. You can only write it inside of the class
		//	return Stack<T, Buffer_size>();
		//}
		static Stack Create();
	};
	template<typename T, size_t Buffer_size>
	Stack<T, Buffer_size> Stack<T, Buffer_size>::Create() {
		// I have to specift all the template types
		return Stack<T, Buffer_size>();
	}
	void classTemplates_subroutine1() {
		Stack<int, 9> stack = Stack<int, 9>::Create();
		Stack<float, 10> s{ 1,2,3,4,5 };
		auto s2(s); // copy constructor
		while (!s.isEmpty())
		{
			std::cout << s.Top() << " ";
			s.Pop();
		}
	}

	// Class Template Specialization
	template<typename T>
	class PrettyPrinter {
	private:
		T* data;
	public:
		PrettyPrinter(T* data) : data(data) {}
		void Print() const {
			std::cout << "{" << *data << "}" << '\n';
		}
		T* GetData() const {
			return data;
		}
		void SetData(T* data) {
			*this->data = *data;
		}
	};
	// Explicit specialization has to be outside the class.
	// I don't need to rewrite all the class for one function
	template<>
	void PrettyPrinter<std::vector<int>>::Print() const {
		std::cout << "class PrettyPrinter<std::vector<int>>: " << "{";
		for (const auto& elem : *data) {
			std::cout << elem << ", ";
		}
		std::cout << "}" << '\n';
	}

	template<>
	class PrettyPrinter<char*> {
	private:
		char* data;
	public:
		PrettyPrinter(char* data) : data(data) {}
		void Print() const {
			std::cout << "class PrettyPrinter<char*>: " << "{" << data << "}" << '\n';
		}
		char* GetData() const {
			return data;
		}
		void SetData(char* data) {
			*this->data = *data;
		}
	};
	template<>
	class PrettyPrinter<std::vector<std::vector<int>>> {
	private:
		std::vector<std::vector<int>>* data;
	public:
		PrettyPrinter(std::vector<std::vector<int>>* data) : data(data) {}
		void Print() const {
			std::cout << "class PrettyPrinter<std::vector<int>>: " << '\n' << "{" << '\n';
			for (const auto& vec_inner : *data) {
				std::cout << "{";
				for (const auto& elem : vec_inner) {
					std::cout << elem << ", ";
				}
				std::cout << "}" << '\n';
			}
			std::cout << "}" << '\n';
		}
		std::vector<std::vector<int>>* GetData() const {
			return data;
		}
		void SetData(std::vector<std::vector<int>>* data) {
			*this->data = *data;
		}
	};

	// non-type template specialization for classes
	template<typename T = int, size_t maxSize = 512>
	class BUFFER {
	private:
		T buffer[maxSize];
	public:
		BUFFER() = default;
		void Print() {
			std::cout << "Using Buffer size: " << maxSize << '\n';
			std::cout << '{' << *buffer << '}' << '\n';
		}
	};
	template<typename T>
	class BUFFER<T, 128> {
	private:
		static const size_t maxSize = 128;
		T buffer[maxSize];
	public:
		BUFFER() = default;
		BUFFER(std::initializer_list<T> li) {
			size_t count = 0;
			for (auto&& elem : li) {
				buffer[count++] = elem;
			}
		}
		void Print() {
			std::cout << "Using Buffer size: " << maxSize << '\n';
			std::cout << '{' << *buffer << '}' << '\n';
		}
	};
	// Partially specialize for array types
	template<typename T>
	class SmartPTR {
	private:
		T* ptr;
	public:
		SmartPTR(T* ptr) : ptr{ ptr }
		{}
		~SmartPTR() {
			delete ptr;
		}

		T* operator->() {
			return ptr;
		}
		T& operator*() {
			return *ptr;
		}
	};

	template<typename T>
	class SmartPTR<T[]> {
	private:
		T* ptr;
	public:
		SmartPTR(T* ptr) : ptr{ ptr }
		{}
		~SmartPTR() {
			delete[] ptr;
		}

		//T* operator->() {
		//	return ptr;
		//}
		//T& operator*() {
		//	return *ptr;
		//}
		T& operator[](size_t idx) {
			return *(ptr + idx);
		}
	};

	void classTemplates_subroutine2() {
		{
			auto data = 5;
			auto dataf = 8.5f;
			PrettyPrinter<int> p1(&data);
			p1.Print();
			PrettyPrinter<float> p2(&dataf);
			p2.Print();

			// one pointer
			const char* str1{ "Mustafa" };
			PrettyPrinter<const char> p3(str1); // T* -> (const char*)* => input is (const char)**
			p3.Print(); // Prints {M}
			const char* theData1 = (p3).GetData(); // T* returns (const char)**
			// two pointer
			const char* str2{ "Mustafa" };
			PrettyPrinter<const char*> p33(&str2); // T* -> (const char*)* => input is (const char)**
			p33.Print(); // prints {Mustafa}
			const char** theData2 = p33.GetData(); // T* returns (const char)**

			// class template specialized for "char*"
			auto str3{ const_cast<char*>("Mustafa") };
			PrettyPrinter<char*> p333(str3); // T* -> (const char*) => input is (const char)*
			p333.Print(); // prints {Mustafa}
			const char* theData22 = p333.GetData(); // T* returns (const char)*
		}

		{
			// class template specialized for "std::vector<int>*"
			std::vector<int> vec{ 1,2,3,4,5 };
			PrettyPrinter<std::vector<int>> pv(&vec);
			pv.Print();

			// class template specialized for "std::vector<std::vector<int>>*"
			std::vector<std::vector<int>> matrix
			{
				{1,2,3,4,5},
				{6,7,8,9,10}
			};
			PrettyPrinter<std::vector<std::vector<int>>> pMatrix(&matrix);
			pMatrix.Print();
		}

		{
			//BUFFER<int, 20> buf{ 1,2,3,4,5,6,7,8,9 }; // !!! ERROR !!! there is no std::initializer implementation constructor
			BUFFER<int, 128> buf{ 1,2,3,4,5,6,7,8,9 }; // specialized for 128

			SmartPTR<int> smartPtr{ new int(2) };
			std::cout << "smartPtr: " << *smartPtr << '\n';

			SmartPTR<int[]> smartPtrArr{ new int(9) };
			smartPtrArr[0] = 8;
			std::cout << "smartPtr: " << smartPtrArr[0] << '\n';
		}

	}

	void classTemplates_Main() {
		// Note: Explicit specialization: Specialize all of them
		// Note: Partial specialization: Specialize small portion of it
		classTemplates_subroutine1();
		classTemplates_subroutine2();
	}
}

namespace typedef_typealias {
	template<typename T = int, size_t size>
	size_t CountSomething(T(&arr)[size], bool(&match)(T)) {
		size_t counter{};
		for (size_t idx = 0; idx < size; ++idx) {
			auto element = arr[idx];
			auto matchResult = match(element);
			if (matchResult) {
				//return idx;
				++counter;
			}
		}
		return counter;
	}

	template<typename T>
	inline bool isEvenOdd(T val, char oddEven) {
		return (val & 1) == oddEven;
	}

	template<typename T1 = int, char oddEven = 0>
	bool isEven(T1 val) {
		return isEvenOdd(val, oddEven);
	}

	template<typename T1 = int, char oddEven = 1>
	bool isOdd(T1 val) {
		return isEvenOdd(val, oddEven);
	}

	// !!! compile-time ERROR !!!
	//bool(&matchEven)(int) = IsEven<oddEven = 0>;
	//bool(&matchOdd)(int) = isOdd<oddEven = 1>;

	bool(&matchEven)(int) = isEven;
	bool(&matchOdd)(int) = isOdd;

	// cannot use template
	typedef std::vector<std::forward_list<std::string>> myDatabase1;
	// I can use template with type alias
	template<typename T>
	using myDatabase2 = std::vector<std::forward_list<T>>;
	void typedef_typealias_subroutine1() {
		/*
		* It is useful for callback functions and event listeners
		*/
		int arr[]{ 1,2,3,4,5 };
		auto counterEven = CountSomething<int>(arr, matchEven);
		std::cout << "How many even values? : " << counterEven << '\n';
		auto counterOdd = CountSomething<int>(arr, matchOdd);
		std::cout << "How many even values? : " << counterOdd << '\n';

		// typedef vs type-alias
		myDatabase1 names1;
		// myDatabase1<std::string> names1; // !!! ERROR !!!

		//myDatabase2 names2; // !!! ERROR !!!
		myDatabase2<std::string> names2;
		myDatabase2<myDatabase2<std::string>> names22;
	}

	template<typename T>
	T Divide(T a, T b) {
		// gives wrong result with "int" (5/2). check it!
		// std::is_floating_point<T>::value is a compile-time expression BUT!
		// inside if calculated at run-time
		// to check it use static_assert
		// use it to check compilation environment
		static_assert(std::is_floating_point<T>::value, "Only floating point types supported");
		if (std::is_floating_point<T>::value == false) // run-time check
		{
			std::cout << "Use floating point types";
			return 0;
		}
		return a / b;
	}

	template<typename T>
	void Check(T&&) {
		// accepts r-value and l-value
		std::cout << std::boolalpha
			<< "Is reference? " << std::is_reference<T>::value << '\n';

		std::cout << "Removing reference\n";
		std::cout << "After removing...: " <<
			std::is_reference<
			typename std::remove_reference<T>::type // depended type to the is_reference
			>::value
			<< '\n';
	}

	void CheckBitSize_runtime() {
		// dynamic dispatch
		if (sizeof(void*) == 4) {
			std::cout << "32 bit env\n";
		}
		else {
			std::cout << "Not 32 bit env\n";
		}
	}

	void CheckBitSize_compiletime() {
		// prevent compilation for specific reason

		//static_assert(sizeof(void*) == 4, "32 bit env\n");
		static_assert(sizeof(void*) != 4, "Not 32 bit env\n");
	}

	void type_traits_subroutine1() {
		/*
		* NOTE: Modern C++(c++11 and c++14)
		* Type traits give the ability to introspect
			* find the characteristics of types at compile time
			* transform the properties of the type
		* Useful in template programing
		* Will either return a boolean or a type when inspecting types
		* Provides template-based interface and defined in header <type_traits>
		* Some traits require support from the compiler
			* compiler provides intrinsics for such traits.

		Note: It is useful when creating extremely high performance application especially calculating at compile time
		*/

		std::cout << std::boolalpha
			<< "Is integer? " << std::is_integral<int>::value << '\n'
			<< "Is integer? " << std::is_integral<double>::value << '\n';

		std::cout << Divide(3.14, 2.78) << '\n';

		Check(5); // r-value
		Integer a{};
		Check(a); // l-value

		CheckBitSize_runtime();
		CheckBitSize_compiletime();
	}

	void typedef_typealias_Main() {
		typedef_typealias_subroutine1();
		type_traits_subroutine1();
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

	class Employee
	{
	private:
		std::string name;
		Integer id;
		Integer salaray;
	public:
		// -*-*-* Constructors *-*-*-
		Employee() = default;
		// -*-*-* Copy Constructor *-*-*-
		template<typename T1, typename T2, typename T3>
		Employee(const T1& name, const T2& id, const T3& salary)
			: name{ name }, id{ id }, salaray{ salary }
		{
			log_function_detail("Employee(const T1& name, const T2& id, const T3& salary)");
		}
		template<>
		Employee(const std::string& name, const Integer& id, const Integer& salary)
			: name{ name }, id{ id }, salaray{ salary }
		{
			log_function_detail("Employee(const std::string& name, const Integer& id, const Integer& salary)");
		}
		// -*-*-* Move Constructor *-*-*-
		template<typename T1, typename T2, typename T3>
		Employee(T1&& name, T2&& id, T3&& salary)
			: name{ std::forward<T1>(name) }, id{ std::forward<T2>(id) }, salaray{ std::forward<T3>(salary) }
		{
			log_function_detail("Employee(T1&& name, T2&& id, T3&& salary)");
		}
		template<>
		Employee(std::string&& name, Integer&& id, Integer&& salary)
			: name{ std::move(name) }, id{ std::move(id) }, salaray{ std::move(salary) }
		{
			log_function_detail("Employee(std::string&& name, Integer&& id, Integer&& salary)");
		}

		// factory method
		template<typename T1, typename T2, typename T3>
		static Employee* CreateEmployee(T1&& name, T2&& id, T3&& salary) {
			return new Employee(std::forward<T1>(name), std::forward<T2>(id), std::forward<T3>(salary));
		}

		// -*-*-* Destructor *-*-*-
		~Employee()
		{
			log_function_detail("~Employee()");
		}
	};


	class Contact
	{
	private:
		std::string name;
		Integer phoneNumber;
		std::string address;
		std::string email;
	public:
		// Constructors
		// Default Constructor
		Contact() = default;
		// Copy Constructor
		template<typename T1, typename T2, typename T3, typename T4>
		Contact(const T1& name, const T2& phoneNumber, const T3& address, const T4& email)
			: name{ name }, phoneNumber{ phoneNumber }, address{ address }, email{ email }
		{
			log_function_detail("ntact(const T1& name, const T2& phoneNumber, const T3& adress, const T4& email)");
		}
		template<>
		Contact(const std::string& name, const uint32_t& phoneNumber, const std::string& address, const std::string& email)
			: name{ name }, phoneNumber{ phoneNumber }, address{ address }, email{ email }
		{
			log_function_detail("ntact(const T1& name, const T2& phoneNumber, const T3& adress, const T4& email)");
		}
		// Move Constructor
		template<typename T1, typename T2, typename T3, typename T4>
		Contact(T1&& name, T2&& phoneNumber, T3&& address, T4&& email)
			: name{ std::forward<T1>(name) }, phoneNumber{ std::forward<T2>(phoneNumber) }, address{ std::forward<T3>(address) }, email{ std::forward<T4>(email) }
		{
			log_function_detail("ntact(const T1& name, const T2& phoneNumber, const T3& adress, const T4& email)");
		}
		template<>
		Contact(std::string&& name, uint32_t&& phoneNumber, std::string&& address, std::string&& email)
			: name{ std::move(name) }, phoneNumber{ std::move(phoneNumber) }, address{ std::move(address) }, email{ std::move(email) }
		{
			log_function_detail("ntact(const T1& name, const T2& phoneNumber, const T3& adress, const T4& email)");
		}

		template<typename T1, typename T2, typename T3, typename T4>
		static Contact* CreateContact(T1&& name, T2&& phoneNumber, T3&& address, T4&& email) {
			return new Contact(std::forward<T1>(name), std::forward<T2>(phoneNumber), std::forward<T3>(address), std::forward<T4>(email));
		}

		// Destructor
		~Contact() {
			log_function_detail("~Contact()");
		}
	};


	// empty creation
	template<typename T>
	T* CreateObject() {
		return new T();
	}
	template<>
	int* CreateObject() {
		return new int;
	}
	template<>
	std::string* CreateObject() {
		return new std::string();
	}
	template<>
	Employee* CreateObject() {
		return new Employee(std::move(std::string()), std::move(Integer{}), std::move(Integer{}));
	}
	template<>
	Contact* CreateObject() {
		return new Contact(std::move(std::string()), std::move(Integer{}), std::move(std::string()), std::move(std::string()));
	}

	// not-empty creation
	template<typename T>
	T* CreateObject(T&& object) {
		return new T(std::forward<T>(object));
	}
	template<>
	int* CreateObject(int&& object) {
		return new int(std::move(object));
	}
	template<>
	std::string* CreateObject(std::string&& object) {
		return new std::string(std::move(object));
	}

	// create with Object itself
	template<>
	Employee* CreateObject(Employee&& contact) {
		return new Employee(std::forward<Employee>(contact));
	}
	template<>
	Contact* CreateObject(Contact&& contact) {
		return new Contact(std::forward<Contact>(contact));
	}

	// create with members
	template<typename T1, typename T2, typename T3>
	Employee* CreateObject(T1&& name, T2&& id, T3&& salary) {
		return CreateEmployee(std::forward<T1>(name), std::forward<T2>(id), std::forward<T3>(salary));
	}
	template<typename T1, typename T2, typename T3, typename T4>
	Contact* CreateObject(T1&& name, T2&& phoneNumber, T3&& address, T4&& email) {
		return CreateContact(std::forward<T1>(name), std::forward<T2>(phoneNumber), std::forward<T3>(address), std::forward<T4>(email));
	}

	// create with only one type
	template<typename T>
	T* CreateObject(std::string&& name, Integer&& id, Integer&& salary) {
		return new T(std::move(name), std::move(id), std::move(salary));
	}
	template<typename T>
	T* CreateObject(std::string&& name, Integer&& phoneNumber, std::string&& address, std::string&& email) {
		return new T(std::move(name), std::move(phoneNumber), std::move(address), std::move(email));
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
		int* p1 = CreateObject<int>(5);
		std::string* s = CreateObject<std::string>();//Default construction

		Employee* emp = CreateObject<Employee>(
			"Bob",    //Name
			101,      //Id
			1000);   //Salary

		Contact* p = CreateObject<Contact>(
			"Joey",                //Name
			987654321,             //Phone number
			"Boulevard Road, Sgr", //Address
			"joey@poash.com");    //Email
	}
	void Assignment_Tests_subroutine() {
		Assignment1_Test();
		Assignment2_Test();
		Assignment3_Test();

	}
}

void Template_Main() {
	Template::Template1_Subroutine();
	Template::Template2_Subroutine();
	PerfectForwarding::PerfectForwarding_Main();
	variadicTemplates::variadicTemplates_Main();
	classTemplates::classTemplates_Main();
	typedef_typealias::typedef_typealias_Main();
	Assignment::Assignment_Tests_subroutine();
}