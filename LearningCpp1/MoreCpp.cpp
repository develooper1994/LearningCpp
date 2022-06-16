#include <iostream>
#include <string>
#include <sstream>


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
	void subroutine1() {

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

	void Assignment1_test() {
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

		const auto& source_temp = ToLower(source);
		const auto& search_string_temp = ToLower(search_string);

		size_t index = source_temp.find(search_string_temp, offset);

		return index; // ISFound ? index : std::string::npos;
	}


	void Assignment2_test() {
		std::cout << std::string("-*-*-*-*") << " Assignment2_test() " << std::string("*-*-*-*-") << '\n';

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
				const auto& pos = Find(test, test_search);
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

	void Assignments_test() {
		Assignment1_test();
		Assignment2_test();

	}
}

void MoreCpp_Main() {
	//Enums::subroutine1();
	//Strings::subroutine1();
	Assignments::Assignments_test();
	literals::subroutine1();
	constexpr_const::subroutine1();
}
