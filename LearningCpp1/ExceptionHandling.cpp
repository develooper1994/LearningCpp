#include <iostream>

#include <malloc.h>
#include <memory>
#include <vector>

#include <numeric>

#include <random>

// Unwinded(en) = çözülmüþ(tr)
/*
* try-catch block working like a switch-case block.
* All standart exception handling classes inherit from a common std::exception, so that can catch all the child class exception even custom exceptions.
* catch (...) // exception base! I can catch all any kind of exceptions. Even not documented!(avoid it. It is default)
*/

namespace ExceptionHandling1 {
	/*
	catch single exception
	*/
	int ProcessLoggingBAD(size_t count)
	{
		// malloc returns nullptr when failed to allocate memory!
		int* arr = (int*)malloc(count * sizeof(int));
		// only way to check error is check if it is nullptr
		if (arr == nullptr) {
			std::cerr << "Failed to allocate memory";
			return -1;
		}
		for (int i = 0; i < count; ++i)
		{
			arr[i] = i * 10;
		}
		free(arr);
		return 0;
	}
	inline void ExceptionHandlingBAD() {
		/*
		Not robust!
		ProcessLoggingBAD doesn't know allocation is succeeded or not and doesn't know what happened in details.
		I can't tell what just happened with some return values in detail.
		Also I can ignore return value. It is bad!
		*/
		ProcessLoggingBAD(std::numeric_limits<size_t>::max()); // allocate extremely large number
	}

	void ProcessLoggingGOOD(size_t count)
	{
		// malloc returns nullptr when failed to allocate memory!
		int* arr = (int*)malloc(count * sizeof(int));
		// only way to check error is check if it is nullptr
		if (arr == nullptr) {
			/*std::cerr << "Failed to allocate memory";
			return -1;*/
			throw std::runtime_error("Failed to allocate memory");
		}
		for (int i = 0; i < count; ++i)
		{
			arr[i] = i * 10;
		}
		free(arr);
		//return 0;
	}
	inline void ExceptionHandlingGOOD() {
		/*
		Robust!
		ProcessLoggingGOOD knows allocation is succeeded or not and knows what happened in details.
		I can tell what just happened with some return values in detail.
		Also I can't ignore return value. It is GOOD!
		I have to use try-throw-catch mechanism to handle this. I can continue to process or just throw exception to the upper blocks
		*/
		try
		{
			ProcessLoggingGOOD(std::numeric_limits<size_t>::max()); // allocate extremely large number
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() << '\n';
		}

	}

	inline void ExceptionHandling1() {
		//ExceptionHandlingBAD();
		ExceptionHandlingGOOD();
	}
}

namespace ExceptionHandling2 {
	/*
	catch multiple exception
	*/
	class Test
	{
	public:
		Test() { std::cout << __FUNCSIG__ << ": Acquire resources\n"; }

		~Test() { std::cout << __FUNCSIG__ << ": Release resources\n"; }
	};

	void ProcessLoggingBetter(size_t count)
	{
		if (count < 10) {
			throw std::out_of_range("Count is should be greater then 10");
		}
		// malloc returns nullptr when failed to allocate memory!
		int* arr = (int*)malloc(count * sizeof(int));
		// only way to check error is check if it is nullptr
		if (arr == nullptr) {
			/*std::cerr << "Failed to allocate memory";
			return -1;*/
			throw std::runtime_error("Failed to allocate memory");
		}
		for (int i = 0; i < count; ++i)
		{
			arr[i] = i * 10;
		}
		free(arr);
		//return 0;
	}

	inline void ExceptionHandlingBetter() {
		try
		{
			//ProcessLoggingBetter(std::numeric_limits<size_t>::max()); // allocate extremely large number

			ProcessLoggingBetter(9);
			//ProcessLoggingBetter(19);
		}
		//catch (const std::runtime_error& ex)
		//{
		//	std::cout << ex.what() << '\n';
		//}
		//catch (std::out_of_range& ex)
		//{
		//	std::cout << ex.what() << '\n';
		//}
		//catch (const std::exception& ex) // standart exception base! I can catch all standart exceptions.
		//{
		//	std::cout << ex.what() << '\n';
		//}
		catch (...) // exception base! I can catch all any kind of exceptions. Even not documented!(avoid it. It is default)
		{
			std::cout << "catch Exception without knowing what it is!\n";
		}
	}

	inline void ExceptionHandling2() {
		ExceptionHandlingBetter();
	}


}

namespace ExceptionHandling3 {
	/*
	Stack and Heap memory management for exception handling.
	Stack created and aquired some resource and release the resources out of the scope. It is called "stack unwinding".
	Heap created and aquired some resource and try to release the resources out of the scope but when exception happens, stay in half of the destruction process.
	*/
	class Test {
	public:
		Test() { std::cout << __FUNCSIG__ << ": Acquire resources\n"; }
		~Test() { std::cout << __FUNCSIG__ << ": Release resources\n"; }
	};

	void ProcessLogging_stack_vs_heap_vs_RAII(size_t count) {
		//Test t_stack1; // stack; Test() and ~Test() will run before exception. Stack objects properly destroyed.
		//Test* t_heap1 = new Test; // heap; Test() will run before exception, however ~Test() could not call due to exception. !!! MEMORY LEAK !!!
		std::unique_ptr<Test> t_smart_pointer(new Test); // the object t_smart_pointer destructor will be invoked. !Always use smart pointers!. !!! RAII saved us !!!
		if (count < 10) { throw std::out_of_range("Count is should be greater then 10"); }

		int* arr_new = new int[count];
		// malloc returns nullptr when failed to allocate memory!
		//int* arr = (int*)malloc(count * sizeof(int)); // use vector instead malloc when allocating array
		// only way to check error is check if it is nullptr
		/*if (arr == nullptr) {
			throw std::runtime_error("Failed to allocate memory");
		}*/

		// Wrong-way to create a vector 
		// it also reserves memory and fills with "0". if you push new elements to vector, it will allocate new memory
		std::vector<int> arr_fill_zeros(count);
		// Correct-way to create a vector
		std::vector<int> arr{};
		arr.reserve(count); // also check if it is available
		for (int i = 0; i < count; ++i)
		{
			// arr[i] = i * 10; // faster. doesn't allocates dynamically. static memory allocated by reserve. You can resize manually
			arr.push_back(i * 10); // slower. allocates dynamically.
		}
		//free(arr); // no need to free memory manually with vector

		delete[] arr_new;
		//delete t_heap1; // cannot delete. There is some exception handling!
	}

	inline void ExceptionHandling_stack_vs_heap_vs_RAII() {
		try
		{
			//ProcessLogging_stack_vs_heap_vs_RAII(std::numeric_limits<size_t>::max()); // allocate extremely large number

			ProcessLogging_stack_vs_heap_vs_RAII(9);
			//ProcessLogging_stack_vs_heap_vs_RAII(19);
		}
		//catch (const std::runtime_error& ex)
		//{
		//	std::cout << ex.what() << '\n';
		//}
		//catch (std::out_of_range& ex)
		//{
		//	std::cout << ex.what() << '\n';
		//}
		//catch (const std::exception& ex) // standart exception base! I can catch all standart exceptions.
		//{
		//	std::cout << ex.what() << '\n';
		//}
		catch (...) // exception base! I can catch all any kind of exceptions. Even not documented!(avoid it. It is default)
		{
			std::cout << "catch Exception without knowing what it is!\n";
		}
	}

	inline void ExceptionHandling3() {
		ExceptionHandling_stack_vs_heap_vs_RAII();
	}
}

namespace ExceptionHandling4 {
	/*
	 Nested Try-catch
	*/

	class Test {
	public:
		Test() { std::cout << __FUNCSIG__ << ": Acquire resources\n"; }
		~Test() { std::cout << __FUNCSIG__ << ": Release resources\n"; }
	};

	void ProcessLogging_Nested(size_t count) {
		std::unique_ptr<Test> t_smart_pointer(new Test);
		if (count < 10) { throw std::out_of_range("Count is should be greater then 10"); }

		std::vector<int> arr{};
		arr.reserve(count);
		for (int i = 0; i < count; ++i) {
			arr.push_back(i * 10);
		}

		std::default_random_engine engine;
		std::bernoulli_distribution distribution; // generates true or false by fifty percent chance.
		auto generator = [&engine, &distribution]() {
			return distribution(engine);
		};

		static size_t error_counter{};
		for (size_t i = 0; i < count; ++i)
		{
			try {
				std::cout << "ProcessLogging # : " << i << ' ';
				auto&& generated = generator();
				if (!generated) {
					// breaks the loop and cannot continue without exception handling :(
					++error_counter;
					throw std::runtime_error("I couldn't continue to process");
				}
				std::cout << '\n';
			}
			catch (std::runtime_error& ex) {
				// something happened but i can continue to process :)
				std::cout << "[ERROR " << ex.what() << "]" << " error counter: " << error_counter << '\n';
				if (error_counter > 4)
				{
					std::runtime_error err("May Day!May Day!May Day! Too many error! nani nani nani... Abandoning operation. booooom! F*ck nuclear power plant blown just right now. F*ck it I am leaving!!!");
					ex = err;
					throw ex; // Just a Proxy. I am throwing what comes to me.
				}
			}
		}

		std::cout << "Total error counter: " << error_counter << '\n';
	}

	inline void ExceptionHandling_Nested() {
		try
		{
			//ProcessLogging_Nested(std::numeric_limits<size_t>::max()); // allocate extremely large number

			//ProcessLogging_Nested(9);
			ProcessLogging_Nested(19);
		}
		//catch (const std::runtime_error& ex)
		//{
		//	std::cout << ex.what() << '\n';
		//}
		//catch (std::out_of_range& ex)
		//{
		//	std::cout << ex.what() << '\n';
		//}
		catch (const std::exception& ex) // standart exception base! I can catch all standart exceptions.
		{
			std::cout << ex.what() << '\n';
		}
		//catch (...) // exception base! I can catch all any kind of exceptions. Even not documented!(avoid it. It is default)
		//{
		//	std::cout << "catch Exception without knowing what it is!\n";
		//}
	}


	inline void ExceptionHandling4() {
		ExceptionHandling_Nested();
	}

}

namespace Constructor_Destructors {
	/*
	Constructor throws an exception destructor does not execute! !!! Memory Leak !!!
	Use smart pointer to solve this issue!
	*/
	class A
	{
	public:
		A()
		{
			std::cout << __FUNCSIG__ << '\n';
		}

		~A()
		{
			std::cout << __FUNCSIG__ << '\n';
		}
	};

	class B
	{
	public:
		B()
		{
			std::cout << __FUNCSIG__ << '\n';
		}

		~B()
		{
			std::cout << __FUNCSIG__ << '\n';
		}
	};

	class Test {
	private:
		// * !!! Memory Leak !!!
		//A* a_pointer{};
		//B b{};
		//int* int_pointer{};
		//char* str{};
		//int* arr{};

		// * !!! No Memory Leak !!!
		std::unique_ptr<A> a_pointer{};
		B b{};
		std::unique_ptr<int> int_pointer{};
		std::unique_ptr<char> str{};
		std::vector<int> arr{};
	public:
		Test() {
			std::cout << __FUNCSIG__ << ": Acquire resources\n";
			// allocate memory inside smart pointer
			a_pointer.reset(new A);

			/*
			* manual memory management doesn't recommended
			a_pointer = new A;
			int_pointer = new int;*/

			throw std::runtime_error("Failed to initialize"); // dummy exception

			/*str = new char[1000];
			arr = new int[5000];*/
		}
		~Test() {
			// avoid throw exception in destructor!
			std::cout << __FUNCSIG__ << ": Release resources\n";

			//throw std::runtime_error("Failed to release");

			// * manual memory management doesn't recommended
			//delete a_pointer;
			//delete int_pointer;
			//delete[] str;
			//delete[] arr;
		}
	};



	void Constructor_Destructors_Main() {
		try {
			Test t1;
			// If destructor throws an exception and other exception thrown by function. program will crashes.
			//throw std::runtime_error{ "What the f...?" };
		}
		catch (const std::exception& ex) {
			std::cout << ex.what() << '\n';
		}
	}
}

namespace noexpt_keyword {
	/*
	* Applied to function(both in decleration & defination)
	* Indicates the function does not throw exceptions
	* Compiler can optimize the function code(promise to compiler like const)
		-> no need to generate "stack unwinding" code
	* An exception from such function terminate the program
		-> stack may or may not be unwinded
	* Not all functions should use noexcept specifier
		-> especially functions calling other functions (in library)
		-> such functions will be exception-neural

	* NOTE: Ideally move and copy constructors, destructors and some other operations are marked with noexcept true specifier.
	This allows certain library functions to decide whether to move or copy the objects. C++ 11, all the destructors are implicitly marked with noexcept specifier.

	* NOTE: Containers(list,vector) will use the move operations only if they have the noexcept(true) specifier.
	This will improve the performance of your code when using your objects with standard containers

	* noexcept by default = noexcept(true)
	* if it is noexcept(false), Debugger can catch the exception.
	*/
	void ThrowException_true(int x = 7) noexcept(true) // if it is false, Debugger can catch the exception.
	{
		throw x;
	}
	void ThrowException_false(int x = 7) noexcept(false) // I am using standard library and cannot guarantied to throws no exception.
	{
		std::cout << x << '\n';
		throw x; // Debugger can catch the exception
	}
	int Sum1(int x, int y) noexcept {
		return x + y;
	}

	int Sum2(int x, int y) noexcept(false) {
		// very simple function. cannot throw exception. but if throws an exception, program immediately terminate and cannot detect error :(
		ThrowException_true();
		return x + y;
	}
	// noexcept(ThrowException_true(x)) returns "ThrowException_true" function can throw exception or not
	// and I can use this value inside "noexcept(noexcept(ThrowException_true(x)))"
	int Sum3(int x, int y) noexcept(noexcept(ThrowException_false(x)))  // noexcept(noexcept(ThrowException_true(x))) 
	{
		// very simple function. cannot throw exception. but if throws an exception, program immediately terminate and cannot detect error :(
		//ThrowException_true();
		ThrowException_false();
		return x + y;
	}

	struct A
	{
		~A() {} // C++ 11, all the destructors are implicitly marked with noexcept specifier
	};

	void noexpt_keyword_Main() {
		A a;
		std::cout << std::boolalpha << noexcept(a.~A()) << '\n'; // noexcept(ThrowException_true(x)) returns "ThrowException_true" function can throw exception or not

		std::cout << std::boolalpha << noexcept(ThrowException_true(7)) << '\n'; // noexcept(ThrowException_true(x)) returns "ThrowException_true" function can throw exception or not
		try {
			Sum3(3, 5);
		}
		catch (const std::exception& ex) {
			std::cout << ex.what() << '\n';
		}
	}
}

void ExceptionHandling_Main()
{
	ExceptionHandling1::ExceptionHandling1();
	ExceptionHandling2::ExceptionHandling2();
	ExceptionHandling3::ExceptionHandling3();
	ExceptionHandling4::ExceptionHandling4();
	Constructor_Destructors::Constructor_Destructors_Main();
	//noexpt_keyword::noexpt_keyword_Main(); // throws some bad exceptions
}