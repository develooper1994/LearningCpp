#include <iostream>
#include <vector>
#include <array>
#include "AllMacrosInOnePlace.h"
#include "MyMath.h"
// My Utility headers
#include "UtilityHeader.h"
// I can write functions to header file but it is not recommended

/*
l-value = left value. VARIABLE
	int x =3;
	int& xref = x;
r-value = right value. numbers, strings

*/

void helloWorld() {
	std::cout << "Hello World!\n Mustafa Selcuk";
}

void comments() {
	// Tek satýrlýk yorum
	/*
	   Çok
	   satýrlý
	   yorum
	*/
}

void ascii() {
	NEWLINE;
	for (size_t i = 32; i < 126; ++i)
	{
		std::cout << i << ((i % 16 == 15) ? '\n' : ' ');
	}
	NEWLINE;
	NEWLINE;

	std::cout << "Printable ASCII [] \n";
	for (char i = ' '; i < '~'; ++i)
	{
		std::cout << i << ((i % 16 == 15) ? '\n' : ' ');
	}
	NEWLINE;
	NEWLINE;

	for (size_t i = 32; i < 126; ++i)
	{
		std::cout << char(i) << ((i % 16 == 15) ? '\n' : ' ');
	}
	NEWLINE;
	NEWLINE;
}

void BasicTypes() {
	std::cout << "Bare bone types \n";
	std::cout << "char: " << "min=" << (int)std::numeric_limits<char>::min() << " " << "max=" << (int)std::numeric_limits<char>::max() << "\n";
	std::cout << "bool: " << "min=" << std::numeric_limits<bool>::min() << " " << "max=" << std::numeric_limits<bool>::max() << "\n";
	std::cout << "int: " << "min=" << std::numeric_limits<int>::min() << " " << "max=" << std::numeric_limits<int>::max() << "\n";
	std::cout << "float: " << "min=" << std::numeric_limits<float>::min() << " " << "max=" << std::numeric_limits<float>::max() << "\n";
	std::cout << "double: " << "min=" << std::numeric_limits<double>::min() << " " << "max=" << std::numeric_limits<double>::max() << "\n";

	std::cout << "\nBare bone signed types \n";
	std::cout << "short int: " << "min=" << std::numeric_limits<short int>::min() << " " << "max=" << std::numeric_limits<short int>::max() << "\n";
	std::cout << "signed int: " << "min=" << std::numeric_limits<signed int>::min() << " " << "max=" << std::numeric_limits<signed int>::max() << "\n";
	std::cout << "long int: " << "min=" << std::numeric_limits<long int>::min() << " " << "max=" << std::numeric_limits<long int>::max() << "\n";
	std::cout << "long long int: " << "min=" << std::numeric_limits<long long int>::min() << " " << "max=" << std::numeric_limits<long long int>::max() << "\n";

	std::cout << "\nBare bone signed types \n";
	std::cout << "unsigned short int: " << "min=" << std::numeric_limits<unsigned short int>::min() << " " << "max=" << std::numeric_limits<unsigned short int>::max() << "\n";
	std::cout << "unsigned int: " << "min=" << std::numeric_limits<unsigned int>::min() << " " << "max=" << std::numeric_limits<unsigned int>::max() << "\n";
	std::cout << "unsigned long int: " << "min=" << std::numeric_limits<unsigned long int>::min() << " " << "max=" << std::numeric_limits<unsigned long int>::max() << "\n";
	std::cout << "unsigned long long int: " << "min=" << std::numeric_limits<unsigned long long int>::min() << " " << "max=" << std::numeric_limits<unsigned long long int>::max() << "\n";
}

void OutputInput() {
	int age;
	std::cout << "What is your age\n";
	std::cin >> age;
	std::cerr << "\nYour age is: " << age;
	std::clog << "\nSome logging\n";


	char name[512];
	std::cout << "What is your name\n";
	std::cin.getline(name, 15);
	std::cout << "Your name is " << name << "\n";
}

void LoopFor() {
	std::vector<int> a;
	for (size_t i = 0; i < 5; ++i)
	{
		int rand_temp = std::rand();
		a.push_back(rand_temp);
		std::cout << a.at(i) << "\n";
	}
}
void loopRangeBased() {
	using namespace std;
	int arr[]{ 10,20,30,40,50 };
	{
		cout << "basic for loop \n";
		for (size_t i = 0; i < 5; i++)
		{
			cout << arr[i] << '\n';
		}
		cout << "range based for loop 1 \n";
		// l-value(variable) range based loop
		for (const auto& i : arr)	 // to prevent copy and changes of value I am using const reference
		{
			// i = 3; // const prevents changes.
			cout << i << '\n';
		}
		// r-value(value) range based loop
		cout << "range based for loop 2 \n";
		for (const auto& i : { 10,20,30,40,50 })	 // to prevent copy and changes of value I am using const reference
		{
			// i = 3; // const prevents changes.
			cout << i << '\n';
		}
	}

	{
		cout << "\nHow range based for loop works internally ?\n";
		cout << "How pointers works internally ?\n";
		// begin and end functions are defined inside all the container header files
		// class should provide '!=' and '==' operators. And also class must provide iterators.
		// be carriful sometimes begin and end are not the same.

		int* beginArr = std::begin(arr); // &arr[0];
		int* endArr = std::end(arr); // &arr[5];

		// double reference(&&) means = convert to r-value(not variable, it is the value).
		auto&& range = arr;
		int* begin = std::begin(range);
		int* end = std::end(range);
		while (begin != end)
		{
			cout << *begin << '\n';
			++begin;
		}
		// OR
		for (; begin != end; ++begin)
		{
			auto temp = *begin;
		}
	}

}
void loopWhile() {
	std::array<std::array<int, 6>, 6> myarray;
	for (auto i = 0; i < myarray.size(); ++i)
	{
		myarray[i].fill(i);
	}

	size_t myArray_outter_size = myarray.size();
	size_t myArray_inner_size = myarray[0].size();

	uint8_t x = 0, y = 0;
	int	trace = 0;
	float normal = 0;

	{
		while (x < myArray_outter_size)
		{
			auto& tempx = myarray.at(x);
			while (y < myArray_inner_size)
			{
				auto& tempxy = tempx.at(y);

				normal += tempxy;

				if (x == y)
				{
					trace += tempxy;
				}
				++y;
			}
			y = 0;
			++x;
		}

		std::cout << "trace= " << trace << "||" << "normal= " << normal << "\n";
	}
	// do-while
	x = 0; y = 0;
	trace = 0;
	normal = 0;
	{
		do
		{
			auto& tempx = myarray.at(x);
			do
			{
				auto& tempxy = tempx.at(y);

				normal += tempxy;

				if (x == y)
				{
					trace += tempxy;
				}
				++y;
			} while (y < myArray_inner_size);
			y = 0;
			++x;
		} while (x < myArray_outter_size);

		std::cout << "trace= " << trace << "||" << "normal= " << normal << "\n";
	}
}
void fibonacciExercise()
{
	// 0, 1, 2, 3, 4, 5, 6,  7,  8,  9, 10, 11,  12, ……..
	// 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, ……..
	// call function from another file
	int n = 10; // 10 unit
	fibonacci_series(n);
	fib_power(n);
}

void Operators()
{
	std::cout << "\nc++ ve ++c farki\n";
	int c = 5;
	int y = c++;
	std::cout << "c= " << c << "\n";
	std::cout << "y= " << y << "\n";
	y = ++c;
	std::cout << "c= " << c << "\n";
	std::cout << "y= " << y << "\n";

	//
	std::cout << "\nc++ ve ++c farký\n";
}
void switchCase() {
	char c = 'M';
	switch (c)
	{
	case 'M':
		std::cout << "Choose is M";
		break;
	case 'u':
		std::cout << "Choose is u";
		break;
	case 's':
		std::cout << "Choose is s";
		break;
	case 't':
		std::cout << "Choose is t";
		break;
	case 'a':
		std::cout << "Choose is a";
		break;
	case 'f':
		std::cout << "Choose is f";
		break;
		/* // duplication Error
		case 'a':
			std::cout << "Chiose is a";
		*/
	default:
		break;
	}
}

void Initializations() {
	/*
	* importants
	1. Value initialization	=> T obj{};
	2. Direct initialization => T obj{v};
	3. Copy initialization => T obj = v; // *** should be avoided ***

	// uniform initialization advantages.
	1. It forces initialization.
	2. You can use direct initialization for array types
	3. It prevents narrowing convertions.(float->int)
	4. Uniform syntax for all types.
	*/


	int a1; //Uninitialized
	int a2 = 0; //Copy initialization
	int a3(5); //Direct initialization
	std::string	s1; //Auto-initialized. There is something to assigning default value inside of class.
	std::string s2("Cpp"); //Direct initialization

	char d1[2]; //Uninitialized
	char d2[5] = { '\0' }; //Copy initialization
	char d3[4] = { 'a', 'b', 'c', 'd' }; //Aggregate(also copy) initialization
	char d4[5] = { "abcd" }; //Copy initialization. There is an invisible char '\0'

	// Default value for all the primitive types are zero.
	int b1{}; //Value initialization
	// int b2(); // !!!ERROR!!! Most vexing parse. Creates and calls an function.
	int b2{ 3 }; //Direct initialization

	int i1[8]{};
	char c2[6]{ "Hello" };

	// If you create an object on the heap and you use value initialization
	// then the object that is created in the heap will have a default value
	int* p1 = new int{};

	char* p2 = new char[8] {};
	char* p3 = new char[6] {"Hello"};


	// Narrowing Conversation
	//float f{};
	//int i{ f }; // !!! ERROR !!!

}


/*
			REFERENCE																		POINTERS
	.Always needs an initializer									.Initializer is optional
	.Initializer should be l-value									.Initializer need not be l-value
	.Cannot be nullptr												.Can be nullptr
	.Bound to its referent											.Can point to other variables
	.No storage required, so has same address as that of referent	. Has its own storage, so will have a different address
	.Deference not required											.Requires dereference operator to access the value

.Reference is not a pointer => (ref != nullptr) is gives an error
*/
void pointers() {
	/*
	1. Pointers should be initialized pointers and variables
	2. Always initialize void pointers and variables
	3. initializer need not be l-value(left value)
	4. Has its own storage so will have a different address
	5. Requires dereference operator to access the value
	*/
	using namespace std;

	// REFERENCE OPERATOR
	int x = 2;
	// void* pointer; // !!! ERROR !!!
	int* px = &x;
	//float* px = &x; // !!! ERROR !!!
	cout << "&x= " << &x << "\n";
	cout << "int px= " << px << "\n";
	void* px1 = &x;	// pointing with another type. Using special cases
	cout << "void px= " << px << "\n";

	// DEREFERENCE OPERATOR
	int x1 = 10;
	int* ptr = &x1;
	*ptr = 5; //Assign 5 of address of x
	int y = *ptr; // Read a value from address of x
	cout << " x= " << x << " \n "
		<< "y= " << y << " \n "
		<< "ptr= " << ptr << " \n "
		<< "*ptr= " << *ptr << " \n ";

	//nullptr
	// Pointers should be initialized so that nullpointer is an placeholder.
	// Access violation does not give build error but it crashes at runtime
	int x2 = 10;
	int* ptr2 = nullptr;
	// auto NullPointerRead = *ptr2; // (Read) Access violation. Program will crash.
	// cout << NullPointerRead << "\n";
	*ptr2 = 10;	// (Write) Access violation. Program will crash.

}
void references() {
	/*
	1. Always needs an initializer
	2. The referent should be a variable
	3. It is bound to its referent
	4. It can be used to modify a variable indirectly(like pointer)
	5. A reference is Not a new varaible, it is just another name
	NO MEMORY ALLOCATED FOR A REFERENCE(micro optimization)

	6. Initializer should be l-value(left value)
	7. cannot be nullptr
	*/
	using namespace std;
	int x = 10;
	int& ref = x;
	cout << "Values of " << "x= " << x << " || " << "ref= " << ref << '\n';
	cout << "Addresses of " << "&x= " << &x << " || " << "&ref= " << &ref << '\n';
	ref = 9865;
	cout << "Values of " << "x= " << x << " || " << "ref= " << ref << '\n';
	cout << "Addresses of " << "&x= " << &x << " || " << "&ref= " << &ref << '\n';
}
void SwapValue(int x, int y)
{
	//pass by value
	auto temp = x;
	x = y;
	y = temp;
}
void SwapPTR(int* x, int* y)
{
	//pass by address(pointer)
	auto temp = *x;
	*x = *y;
	*y = temp;

}
void SwapREF(int& x, int& y)
{
	//pass by reference
	// I can change variables without using pointer syntax.
	auto temp = x;
	x = y;
	y = temp;

}
void printPTR(int* ptr)
{
	using namespace std;
	if (ptr != nullptr)
	{
		cout << *ptr << '\n';
	}
}
void printREF(int& ref)
{
	using namespace std;
	// if (ref != nullptr) cout << ptr << '\n'; // !!! ERROR !!!
	cout << ref << '\n';
}
void PTRvsREF() {
	using namespace std;
	//std::string* name = "Mustafa"; // not allowed
	//std::string& name = "Mustafa"; // not allowed

	// SWAP
	int x = 1, y = 20;
	SwapValue(x, y);
	cout << "SwapValue " << "x= " << x << " || " << "y= " << y << '\n';
	x = 1, y = 20;
	SwapPTR(&x, &y);
	cout << "SwapPTR   " << "x= " << x << " || " << "y= " << y << '\n';
	x = 1, y = 20;
	SwapREF(x, y);
	cout << "SwapREF   " << "x= " << x << " || " << "y= " << y << '\n';

	// Print
	printPTR(nullptr);
	// printREF(nullptr); // !!! ERROR !!!

}

// const = constant
void constants() {
	/*
	1. It is a check for compiler. Value fixed at ***compile time***. Attempt to change will cause complitations error. So there is no equivalent in asm.
	2. Replaces C Macros. (Macros has some disadvantages hard to debug.)
	3. Commonly used with references
	4. Code becomes more readable.
	5. Prevents accidental changes.
	(Compiler makes some micro optimizations if variables are const)

	!!! References can change like variables so that
	Argument by references should be ***const ref*** !!!
	*/

	using namespace std;
	{
		// Area of circle
		cout << "Area of circle\n";
		const float PI{ 3.141f };
		//PI = 3; // !!! ERROR !!!
		float rad = 0;
		cout << "Please enter the radious= \n";
		cin >> rad;
		auto area = PI * pow(rad, 2);
		const float circumference = PI * 2 * rad; // I can assign value of const after calculations.
		cout << "Rad= " << rad << " area= " << area << " circumference= " << circumference << '\n';
	}

	{
		// const ptr
		cout << "const ptr\n";
		const int BIT_SIZE = 64;
		// int* ptr1 = &BIT_SIZE; // !!! ERROR !!! // You cannot create not const ptr to const value
		const int* ptr1 = &BIT_SIZE;
		// *ptr1 = 1; // !!! ERROR !!! // Value is const

		int x = 10;
		// ptr = &x;// !!! ERROR !!! // Ptr is const
		auto printPTR = [](int* ptr)
		{
			std::cout << "print function= " << *ptr << '\n';
			*ptr = 56; // accidental change

		}; // lambda(anonymous-small-inner) function, function pointer
		printPTR(&x);
		cout << "main->x= " << x << '\n';


		auto printREF = [](const int& ptr)
		{
			std::cout << "print function= " << ptr << '\n';
			// ptr = 984653; // prevents accidental change
		};  // lambda(anonymous-small-inner) function, function pointer
		printREF(x); // pssing variable(lvalue) as referance
		cout << "main->x= " << x << '\n';
	}

	{
		// Some other exercises
		int x = 5;
		const int MAX = 12;
		int& ref_x1 = x;
		ref_x1 = 777;
		const int& ref_x2 = x;
		// ref_x2 = 666; // !!! ERROR !!!

		const int* ptr1 = &x;
		//*ptr1 = 0; // !!! ERROR !!!
		int* const ptr2 = &x;
		//*ptr1 = 0; // !!! ERROR !!!
		const int* const ptr3 = &x;
		//*ptr1 = 0; // !!! ERROR !!!

		const int* _ptr3 = &ref_x1;
		// int* ptr4 = ref_x2;	// !!! ERROR !!! // ref_x2 is const ref but ptr4 is not const ptr

		const int& r1 = ref_x1;
		// int& r2 = ref_x2; // !!! ERROR !!! // ref_x2 is const ref but r2 is not const ref

		// int* p_ref1 = ptr1;	// !!! ERROR !!! // ref_x2 is const ref but p_ref1 is not const pointer
		// const int*& p_ref2 = ptr2;
	}

}

void autoKeyWord() {
	auto i = 10;
	auto j = 5;
	auto sum = i + 4.3f; // float

	auto result = add(i, j); // int
	static auto y = 2; // int
	const int x = 1;
	const auto var = x;  // const int
	// !!! You should avoid auto when initializting references or pointers. !!!
	auto& var1 = x; // const int &
	auto ptr1 = &x; // const int *
	auto* ptr2 = &x; // const int *

	auto val{ 1 };
	// auto list{ 1,2,3,4, }; // !!! ERROR !!! // Requires '=' operator
	auto list = { 1,2,3,4, };  // std::initializer_list<int>
}

//	Function Pointer					vs		Function Reference
// void (*pfn) (int, char) = &Print;		void(&prn)(int, char) = Print;
//
// Function Pointer
void FunctionPointer() {
	// It is an old c language function. Location of it doesn't matter. It will be executed at the exit. It is guarantied.
	// atexit has function pointer inside.
	atexit(EndMessage);
	using namespace std;
	cout << "function itself\n";
	Print(5, '#');
	void (*pfn) (int, char) = &Print;
	cout << "function pointer\n";
	(*pfn)(5, '\'');
	// OR
	pfn(5, '*');
	cout << "End of FunctionPointer\n";

}

// Function Reference
void FunctionReference() {
	// It is an old c language function. Location of it doesn't matter. It will be executed at the exit. It is guarantied.
	// atexit has function pointer inside.
	atexit(EndMessage);
	using namespace std;
	cout << "function it self\n";
	Print(5, '#');
	void(&prn)(int, char) = Print;
	cout << "function pointer\n";
	(prn)(5, '\'');
	// OR
	prn(5, '*');
	cout << "End of FunctionPointer\n";
}

// a namespace definition must appear either at file scope or immediately within another namespace definition

namespace Astronomy {
	float Calculation(float x, float y)
	{
		return (x + y) / 2;
	}
}
namespace Chemistry {
	float Calculation(float x, float y)
	{
		return x * y;
	}
}
namespace Sorting {
	void quicksort() {}
	void bubblesort() {}
	void mergesort() {}
	namespace Comparision {
		void Less() {}
		void Greater() {}
	}
}
namespace {
	// If you want something internal use like this. It is similar to C# seal classes
	// It is internal function. It cannot access from another file. It is only visible in "EducationFunction.h"
	void Internal() {}
}
void NamespaceCpp()
{
	auto x = 3.141f, y = 2.828f;
	auto res1 = Astronomy::Calculation(x, y);
	auto res2 = Chemistry::Calculation(x, y);
	std::cout << "Astronomy::Calculation(x, y): " << res1 << '\n';
	std::cout << "Chemistry::Calculation(x, y): " << res2 << '\n';
	using Astronomy::Calculation;
	res1 = Calculation(x, y);
	res2 = Chemistry::Calculation(x, y);
	std::cout << "Astronomy::Calculation(x, y): " << res1 << '\n';
	std::cout << "Chemistry::Calculation(x, y): " << res2 << '\n';

	/*
	// It causes conflicts.	Which namespace? Astronomy or Chemistry?
	using Chemistry::Calculation;
	res2 = Calculation(x, y); // !!! ERROR !!!*/

	// full qualified name for less and greater functions
	Sorting::Comparision::Less();
	Sorting::Comparision::Greater();

	// nameless namespace functions can be used without declaring namespace
	Internal();
}

// !!! Important Problems !!!
namespace VexginParse {
	// reference: https://www.youtube.com/watch?v=ByKf_foSlXY
	struct Type {
		int data = 42;
	};
	// Function pointer: Type (*) () // returns "Type" and takes zero parameters.
	// Function reference: Type (); // returns "Type" and takes zero parameters.
	void VexginParse_main() {
		// Most vexing parse happens here
		{
			Type val(); // it is actually function declaration
			// auto result = val.data; // !!! Compiler ERROR !!!
			//auto result = val().data; // !!! ERROR !!! calls unknown function and gets unknown data.
			//std::cout << "data: " << result << '\n';
		}

		// Most reasonable approach is without parenthesis "()"
		{
			Type val;
			auto result = val.data; // !!! ERROR !!! calls unknown function and gets unknown data.
			std::cout << "data: " << result << '\n';
		}
	}

	// Ok! I am defining the function
	Type val() {
		// just return the think that you should be returning in here.
		return {}; // return the default object. default object has "data=42"
	}
}

namespace Weirdness {
	struct ST {
		int x = 15;
		int y = 20;
	};

	void test() {
		int a[]{ 1,2,3,4,5 };
		std::cout << "\nWeird array access\n";
		// all of them gives the same result.
		std::cout << "a[3]= " << a[3] << '\n';
		std::cout << "*(a + 3)= " << *(a + 3) << '\n';
		std::cout << "*(3 + a)= " << *(3 + a) << '\n';
		std::cout << "3[a] = " << 3[a] << '\n'; // It is also valid for some reason.

		std::cout << "\nWeird struct access\n";
		ST data;
		std::cout << "data.x= " << data.x << '\n';
		// "data.y" and "*(&(data.x) + 1)" gives the same result.
		std::cout << "data.y=" << "*(&(data.x) + 1)= " << *(&(data.x) + 1) << '\n'; // take the address "&(data.x)" forward 1 and access the data from the address.
	}
}

void LanguageBasics_Main() {
	// helloWorld();
	// comments();
	ascii();
	// BasicTypes();
	// OutputInput();

	//loops
	// LoopFor();
	// loopRangeBased();
	// loopWhile();
	// fibonacciExercise();

	//Memory
	// Initializations();
	// pointers();
	// references();
	// PTRvsREF();
	// constants();
	// autoKeyWord();

	// Operators();
	// switchCase()
	// FunctionPointer();

	// !!! Important Problems !!!
	//VexginParse::VexginParse_main();
	//Weirdness::test();
	// !!! zero width space character(U+200B) !!! => invisible unicode character that causes compiler syntax errors you can't see. It is a nightmare :@

	// homeworks
	HomeWork1::homework1_test();
}
