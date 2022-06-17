#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

#include <initializer_list>
#include <vector>
#include <array>

#include <ranges>
#include <algorithm>

namespace Enums {
	// Enum elements are accessible in the scope
	// https://www.programiz.com/cpp-programming/enumeration
	enum season { spring, summer, autumn, winter };
	enum smallenum : std::int16_t
	{
		sa,
		sb,
		sc
	};
	enum directions { north = 90, south = -90, east = 0, west = -180 };
	// https://en.cppreference.com/w/cpp/language/enum
	enum { a, b, c = 0, d = a + 2 }; // defines a = 0, b = 1, c = 0, d = 2

	void subroutine1() {
		enum week { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };
		week today;
		today = Friday;
		std::cout << "Day: " << today + 1 << '\n';

		//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
		enum designFlags {
			// since the power of 2, I can combine flags at once without overlapping using bitwise OR(|)
			// You see it in win32 applications.
			BOLD = 1,		// 00000001
			ITALICS = 2,	// 00000010
			UNDERLINE = 4	// 00000100
		};
		directions direct{};
		std::cout << "sizeof(week)= " << sizeof(week) << '\n';

		int my_design = BOLD | UNDERLINE; // 00000101
		std::cout << my_design << '\n';
		if (my_design & ITALICS) // 00000101 & 00000010 = 00000000
		{
			// do something about Italics
		}

		//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
		// Struct and Classes with enums have exactly the same meaning.
		// It just makes Enum elements limits access. Accessible locally.
		// c++ 11
		enum class coordinates { x, y };
		enum struct Y
		{
			left = 'l', right = 'r'
		};
		enum struct altitude : char
		{
			left = 'l', right = 'r'
		};
		enum class altitude2 : char
		{
			high = 'h',
			low = 'l', // trailing comma only allowed after CWG518
		};

		//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
		// old
		struct X
		{
			enum direction { left = 'l', right = 'r' };
		};
		X x;
		X* p = &x;
		int a = X::direction::left; // allowed only in C++11 and later
		int b = X::left;
		int c = x.left;
		int d = p->left;

		//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

		// Enum and Switch-case are perfect match.
		enum class Color { red, green = 20, blue };
		// Color r = blue; // !!! ERROR !!!
		Color r = Color::blue;
		switch (r) {
		case Color::red: std::cout << "red\n";   break;
		case Color::green: std::cout << "green\n"; break;
		case Color::blue: std::cout << "blue\n";  break;
		default: break;
		}
		// int n = r; // error: no implicit conversion from scoped enum to int
		int n = static_cast<int>(r); // OK, n = 21
		//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

	}
}

namespace Strings {
	const char* oldCombine(const char* s1, const char* s2) {
		int n = strlen(s1) + strlen(s2) + 1;
		char* temp = new char[n];
		strncpy_s(temp, n, s1, n);
		strncat_s(temp, n, s2, n);
		return temp;
	}
	void oldStyle() {
		char first[10];
		char second[10];
		std::cin.getline(first, 10);
		std::cin.getline(second, 10);

		const char* FullName = oldCombine(first, second);
		std::cout << FullName << '\n';
		delete[] FullName;
	}

	std::string newCombine(const std::string& s1, const std::string& s2) {
		std::string temp = s1 + s2;
		return temp;
	}
	void newStyle() {
		// Initialize and assign
		std::string s{ "Mustafa" };
		s = "Murtaza";

		// Access
		s[0] = 'W';
		char ch = s[0];

		std::cout << s << '\n';
		std::cin >> s; // old c++ way

		std::getline(std::cin, s);	// #include <string>
		// Size
		s.length();

		// Insert &concatenate
		std::string s1("Sugar"), s2{ "Zugar" };
		s = s1 + s2;
		s += s1;

		s.insert(6, "World");
		// Comparison
		if (s1 != s2)
		{
			std::cout << "You right\n";
		}

		// Removal
		s.erase(2); // erase until 2.index
		s.clear(); // erases all string
		s.erase(); // s.clear();

		// Search
		auto pos = s.find("Sugar", 0);
		if (pos != std::string::npos) // std::string::npos is -1
		{
			std::cout << "\nfound\n";
		}
		else
		{
			std::cout << "\nnot found\n";
		}


		// Same application oldStyle
		std::string first;
		std::string second;

		std::getline(std::cin, first); // #include <string>
		std::getline(std::cin, second); // #include <string>

		std::string FullName = first + second;
		std::cout << "std::string: " << FullName << '\n';
		std::cout << "std::string c style: " << FullName.c_str() << '\n';

		using namespace std::string_literals;
		auto a = "asf";  // const char *
		auto b = "asf"s; // std::string
	}

	void stringStream() {
		int a{ 5 }, b{ 8 };
		int sum = a + b;
		std::cout << "Sum of " << a << " of " << b << " is : " << sum << '\n';

		//std::stringstream ss; // stringstream
		//std::istringstream is; // input stringstream
		//std::ostringstream os; // output stringstream

		std::stringstream output;
		output << "Sum of " << a << " of " << b << " is : " << sum; // #include <sstream>

		output.str("I can insert stringstream");
		std::string internal_string = output.str(); // stringstream to string
		std::string st = std::to_string(sum); // num to string

		std::cout << "stringstream= " << output.str() << '\n';
		std::cout << "st= " << st << '\n';

		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
		std::string encodded = "10 11 12";
		int a2;
		std::stringstream ss;
		ss.str(encodded);
		// writes last element twice
		//while (!ss.fail()){
		//	ss >> a2;
		//	std::cout << a2 << '\n';
		//}
		while (ss >> a2) {
			std::cout << a2 << '\n';
		}

		std::cout << std::stoi("54") << '\n';  // string to int
		std::cout << std::stof("55") << '\n';  // string to float
		std::cout << std::stod("56") << '\n';  // string to double
		std::cout << std::stoull("57") << '\n';  // string to unsigned long long
	}

	void subroutine1() {
		oldStyle();
		newStyle();
		stringStream();
	}
}

namespace literals {
	/*
	<type> operator"" _<literal-name>(){}
	- user defines literals must be specified with '_'. Others reserved by compilers.
	- only following types can be suffixed to make a user-defined literal: unsigned long long, long double, const char*, char
	- cannot overload build-in literals.
	- Literal operator functions cannot be member functions.
	*/
	class Distance
	{
	private:
		long double mem_km;
	public:
		Distance(long double km) : mem_km{ km } {}
		long double SetKm() const {
			return mem_km;
		}
		~Distance() = default;
	};
	Distance operator"" _mi(long double val) {
		return Distance{ val * 1.6 };
	}
	Distance operator"" _metre(long double val) {
		return Distance{ val / 1000 };
	}

	void subroutine1() {
		Distance dist1{ 32.0 };
		Distance dist2{ 32.0_mi };
		Distance dist3{ 32.0_metre };

	}
}

namespace constexpr_const {
	// It is a extended const keyword.
	// Compiler tried to calculate at compile time.
	// Can be applied to variable declarations or functions
	// May increase performance
	/*
	- I can apply constexpr to only literal types and function that only uses literal types.
	- Should accept and return literal types only(void, scalar types(void,float,char,...) references, etc...)
	- constexpr functions implicitly inline functions so that they should be defined inside "header"
	*/

	// int Get() { return 42; } // computed at run-time
	// constexpr int Get() { return 42; } // computed at compile-time
	//They are the same but some const expressions evaluated at compile time.

	constexpr int i = 10;
	int arr[i];

	const int j = 10;
	int arr2[j];

	constexpr int Max(int x, int y) {
		return x > y;
	}

	constexpr int factorial(uint32_t x) {
		if (x < 0) {
			std::cerr << "Error! Factorial of a negative number doesn't exist.";
			return -1;
		}
		int temp = 1;
		for (size_t i = 1; i <= x; ++i) {
			temp *= i;
		}
		return temp;
	}

	void subroutine1() {
		constexpr int fact = factorial(5);
		std::cout << "constexpr Max: " << Max(10, 15) << '\n';
		std::cout << "constexpr factorial: " << fact << '\n';
	}
}

namespace initializer_list_space {
	/*
	- Lightweight proxy object that represents an array of objects
	- Constructed automatically from a braced list of elements: auto, range based for loop, constructor, function.

	*/
	class Bag
	{
	private:
		int arr[10];
		int size{};
	public:
		Bag() = default;
		Bag(std::initializer_list<int> values) {
			std::cout << "Bag(std::initializer_list<int> values)\n";
			assert(values.size() < 10);
			auto iter = values.begin();
			while (iter != values.end())
			{
				Add(*iter);
				++iter;
			}
		}
		void Add(int value) {
			assert(size < 10);
			arr[size++] = value;
		}
		void Remove() {
			--size;
		}
		int operator[](int index) {
			return arr[index];
		}
		int GetSize()const {
			return size;
		}
	};
	void Display(std::initializer_list<int> values) {
		auto iter = values.begin();
		//while (iter != values.end())
		//{
		//	std::cout << *iter << ' ';
		//}
		for (auto x : values)
		{
			std::cout << x << ' ';
		}
	}
	void subroutine1() {
		int x{ 0 };
		int y{}; // 0
		float z{ 3.14f };
		int arr[5]{ 3,1,4,1,0 };
		std::string s{ "Gümüþhane" };
		std::initializer_list<int> data{ 1,2,3,4 };
		auto values = { 1,2,3,4, };
		// auto values{ 1,2,3,4, }; // !!! ERROR !!!

		// without initializer_list
		Bag bag; // Bag()
		bag.Add(3);
		bag.Add(1);
		bag.Add(4);
		for (size_t i = 0; i < bag.GetSize(); i++)
		{
			std::cout << "bag[" << i << "]" << bag[i] << '\n';
		}
		// with initializer_list
		Bag bag2{ 3,1,4 }; // Bag(std::initializer_list<int> values)
		for (size_t i = 0; i < bag2.GetSize(); i++)
		{
			std::cout << "bag2[" << i << "]" << bag2[i] << '\n';
		}

		Display({ 1,2,3,4,5 });
	}
}

namespace vector {
	void subroutine1() {
		std::vector<int> data{ 1,2,3 };
		for (size_t i = 0; i < 5; i++)
		{
			data.push_back(i * 10);
		}
		//Access
		data[0] = 111;
		for (size_t i = 0; i < data.size(); i++)
		{
			std::cout << data[i];
		}
		std::cout << '\n';

		data.at(1) = 10;
		for (auto v : data)
		{
			std::cout << v;
		}
		std::cout << '\n';

		auto begin = data.begin();
		auto begin_3 = *(begin + 3);
		std::cout << begin_3 << '\n'; // 3. index
		auto end = data.end();
		for (auto v = begin; v < end; ++v)
		{
			std::cout << *v;
		}
		std::cout << '\n';

		//Delete
		auto iter = data.begin();
		data.erase(iter);
		for (auto x : data) {
			std::cout << x << ' ';
		}
		std::cout << '\n';

		//Insert
		iter = data.begin() + 4;
		data.insert(iter, 555);
		for (auto x : data) {
			std::cout << x << ' ';
		}
		std::cout << '\n';

	}
}

namespace Unions {
	/*
	Struct holds data in separate
	Union holds data in same memory. Size of union will be equal to size of its largest member, and that could be used for storage.

	- Saves space(embedded applications)
	- no way to know which type it holds
	- Nested types with non-default constructor deletes the default constructor of the union
	- cannot assign objects of user defined types directly to a union member
	- user defined types are not destroyed implicitly
	- cannot have a base class
	- cannot derive from a union
	- cannot contain virtual funtions.
	NOTE: If you have to use union you have really know what you are doing. Unions have many restrictions.
	NOTE: C++ 17 introduces variants as type safe union.
	*/
	// To show which method calling, use "__FUNCSIG__"
	union Test
	{
		int x; // size of union is 4.
		char ch;
		double d; // size of union is 8 now.
		Test() : ch{ 'c' } //x{ 0 }, ch{ 's' }	  // you can initialize only one member
		{
			std::cout << __FUNCSIG__ << "\n";
		}
		~Test() {
			std::cout << __FUNCSIG__ << "\n";
		}
	};

	// A and B structs are dummy. Don't care about them :)
	// except that I have implemented all the functions from rules of classes
	struct A {
		// default
		A() {
			std::cout << __FUNCSIG__ << '\n';
		}
		~A() {
			std::cout << __FUNCSIG__ << '\n';
		}
		// copy
		A(const A& obj)
		{
			std::cout << __FUNCSIG__ << '\n';
		}
		A& operator=(const A& obj)
		{
			std::cout << __FUNCSIG__ << '\n';
			return this == &obj ? *this : *this;
		}
		// move
		A(A&& obj)
		{
			std::cout << __FUNCSIG__ << '\n';
		}
		A& operator=(A&& obj)
		{
			std::cout << __FUNCSIG__ << '\n';
			return this == &obj ? *this : *this;
		}
	};
	struct B {
		// default
		B() {
			std::cout << __FUNCSIG__ << '\n';
		}
		~B() {
			std::cout << __FUNCSIG__ << '\n';
		}
		// copy
		B(const B& obj)
		{
			std::cout << __FUNCSIG__ << '\n';
		}
		B& operator=(const B& obj)
		{
			std::cout << __FUNCSIG__ << '\n';
			return this == &obj ? *this : *this;
		}
		// move
		B(B&& obj)
		{
			std::cout << __FUNCSIG__ << '\n';
		}
		B& operator=(B&& obj)
		{
			std::cout << __FUNCSIG__ << '\n';
			return this == &obj ? *this : *this;
		}
	};
	union Union_Data_Types {
		A a; // defined but not created
		B b; // defined but not created
		std::string str; // defined but not created // largest member ;)
		// A and B have user defined default constructors. The default constructor and destructor of union becomes deleted.
		Union_Data_Types() {
			std::cout << __FUNCSIG__ << '\n';
		}
		~Union_Data_Types() {
			std::cout << __FUNCSIG__ << '\n';
		}
	};
	void subroutine1() {
		Test t;
		std::cout << sizeof(t) << '\n';

		std::cout << t.ch << '\n';
		t.x = 1000;
		std::cout << t.ch << '\n';

		Union_Data_Types U;
		//U.a = A{}; // !!! ERROR !!! You can use the assignment operator only when the instances have been created.
		using namespace std::string_literals;
		//U.str = "dsahfgjmk"s; // !!! CRASH !!! // doesn't allocate memory ;)

		// -*-*-*-* rigth way with unions *-*-*-*-
		// new(<address of the member>) <type>{"data"};
		// doesn't call user defined types of destructor automatically. You have delete manually
		new(&U.str) std::string{ "asdfasdf" }; // You have to allocate memory 
		new(&U.a) A{};
		new(&U.b) B{};

		U.a.~A();
		U.b.~B();



	}
}

namespace Assignments {
	void IsTestSuccessed(const int& test_cases_size, const int& test_count) {
		if (test_cases_size == test_count)
		{
			std::cout << "TEST SUCCESSED :D\n";
		}
		else
		{
			std::cout << "TEST FAILED :((\n";
		}
	}
	const auto BigMin = 'A';
	const auto BigMax = 'Z';
	const auto smallMin = 'a';
	const auto smallMax = 'z';
	const auto fark = (smallMin - BigMin); // 97 - 65 = 32
	const auto IsBigChar = [](const char& c) { return c >= BigMin && c <= BigMax; };
	const auto IsSmallChar = [](const char& c) { return c >= smallMin && c <= smallMax; };
	const auto IsAlphabet = [](const char& c) {return IsBigChar(c) || IsSmallChar(c); };
	std::string ToUpper(const std::string& str) {
		auto lenght = str.length();
		std::string temp("");
		for (size_t i = 0; i < lenght; ++i)
		{
			const auto& cc = str.at(i);
			auto&& c = static_cast<int>(cc); // must be lvalue
			//char& offset{ cc };
			if (IsAlphabet(c) && !IsBigChar(c)) {
				c = static_cast<char>(c - fark);
			}
			temp += c;
		}
		return std::string(temp);
	}
	std::string ToLower(const std::string& str) {
		auto lenght = str.length();
		std::string temp("");
		for (size_t i = 0; i < lenght; ++i)
		{
			const auto& cc = str.at(i);
			auto&& c = static_cast<int>(cc); // must be lvalue
			//char& offset{ cc };
			if (IsAlphabet(c) && !IsSmallChar(c)) {
				c = static_cast<char>(c + fark);
			}
			temp += c;
		}
		return std::string(temp);
	}
	void AssignmentToUpperToLower_test() {
		std::cout << std::string("-*-*-*-*") << " Assignment1_test() " << std::string("*-*-*-*-") << '\n';

		std::vector<std::string> test_cases{ "AAA", "aaa", "AbCde", "1AbC1d2e3", "!1'A^b+C%1&d/2(e)3=?-_" };
		auto test_count = 0;
		for (auto&& test : test_cases) {
			++test_count;
			std::cout << test_count << ") " <<
				"test: " << test << " || " <<
				"ToUpper: " << ToUpper(test) << '\n' <<
				"ToLower: " << ToLower(test) << '\n';
		}


		IsTestSuccessed(test_cases.size(), test_count);
	}

	enum class Case { SENSITIVE, INSENSITIVE };
	size_t Find(
		const std::string& source,         //Source string to be searched
		const std::string& search_string,  //The string to search for
		Case searchCase = Case::INSENSITIVE,//Choose case sensitive/insensitive search
		size_t offset = 0) {                //Start the search from this offset
		//Implementation

		/*
		return position of the first character
		of the substring, else std::string::npos
		*/

		auto source_temp{ source };
		auto search_string_temp{ search_string };
		if (searchCase == Case::INSENSITIVE) {
			source_temp = ToLower(source);
			search_string_temp = ToLower(search_string);
		}
		// <body>
		size_t index = source_temp.find(search_string_temp, offset);
		// </body>

		return index; // ISFound ? index : std::string::npos;
	}
	void AssignmentFind_test() {
		std::cout << '\n' << std::string("-*-*-*-*") << " AssignmentFind_test() " << std::string("*-*-*-*-") << '\n';

		std::vector<std::string> test_cases{ "AAA", "aaa", "AbCde", "1AbC1d2e3", "!1'A^b+C%1&d/2(e)3=?-_" };
		std::vector<std::string> test_search_string_cases{
			"A", "AA",
			"a", "aa",
			"Ab", "aB",
			"Cd", "de",
			"1", "1A", "C1", "d2e3", "d2e33", "d2ee", "d2e3e",
			"A^b+C%1&d/2(e)", "\"A^b+C%1&d/2(e)"
		};

		auto test_count = 0;
		std::string found = "not found";
		for (auto&& test : test_cases) {
			for (auto&& test_search : test_search_string_cases)
			{
				++test_count;
				const auto& pos = Find(test, test_search, Case::INSENSITIVE);
				found = pos != std::string::npos ? "found" : "not found";
				std::cout << test_count << ") " <<
					"test: " << test << " || " <<
					"test_search: " << test_search << " || " <<
					"Find: " << found <<
					"Position: " << pos <<
					" \n";
			}
		}


		auto allTestCount = test_cases.size() * test_search_string_cases.size();
		IsTestSuccessed(allTestCount, test_count);
	}

	std::vector<int>
		FindAll(
			const std::string& source,              //Target string to be searched
			const std::string& search_string,       //The string to search for
			Case searchCase = Case::INSENSITIVE,    //Choose case sensitive/insensitive search
			size_t offset = 0) {                    //Start the search from this offset
		//Implementation

	   /*
	   Return indices of found strings,
	   else an empty vector
	   */

		auto source_temp{ source };
		auto search_string_temp{ search_string };
		if (searchCase == Case::INSENSITIVE) {
			source_temp = ToLower(source);
			search_string_temp = ToLower(search_string);
		}

		// <body>
		size_t index = 0;
		std::vector<int> allIndexes;
		while (
			index = Find(source, search_string, searchCase, offset + index),
			index != std::string::npos
			)
		{
			allIndexes.push_back(index);
			++index;
		}
		/*for (size_t index = 0; index != std::string::npos; index++)
		{
			index = Find(source, search_string, Case::INSENSITIVE, offset + index);
			if (index == std::string::npos) {
				return allIndexes;
			}
			allIndexes.push_back(index);
		}*/
		// </body>


		return allIndexes;
	}

	void AssignmentFindAll_test() {
		std::cout << '\n' << std::string("-*-*-*-*") << " AssignmentFindAll_test() " << std::string("*-*-*-*-") << '\n';

		std::vector<std::string> test_cases{ "AAA", "aaa", "AbCde", "1AbC1d2e3", "!1'A^b+C%1&d/2(e)3=?-_" };
		std::vector<std::string> test_search_string_cases{
			"A", "AA",
			"a", "aa",
			"Ab", "aB",
			"Cd", "de",
			"1", "1A", "C1", "d2e3", "d2e33", "d2ee", "d2e3e",
			"A^b+C%1&d/2(e)", "\"A^b+C%1&d/2(e)"
		};

		auto test_count = 0;
		std::string found = "not found";
		for (auto&& test : test_cases) {
			for (auto&& test_search : test_search_string_cases)
			{
				++test_count;
				const auto& pos = FindAll(test, test_search, Case::INSENSITIVE);
				found = !pos.empty() ? "found" : "not found";
				std::cout << test_count << ") " <<
					"test: " << test << " || " <<
					"test_search: " << test_search << " || " <<
					"Find: " << found <<
					" \n";
			}
		}


		auto allTestCount = test_cases.size() * test_search_string_cases.size();
		IsTestSuccessed(allTestCount, test_count);
	}



	void Assignments_test() {
		AssignmentToUpperToLower_test();
		AssignmentFind_test();
		AssignmentFindAll_test();

	}
}

void MoreCpp_Main() {
	Enums::subroutine1();
	Strings::subroutine1();
	literals::subroutine1();
	constexpr_const::subroutine1();
	initializer_list_space::subroutine1();
	vector::subroutine1();
	Unions::subroutine1();


	Assignments::Assignments_test();
}
