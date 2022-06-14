#include <iostream>
#include <string>
#include <sstream>


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
		// std::cin >> s; // Throws exception

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
		s.erase(); // s.clear();
		s.erase(2); // erase 2.index
		s.clear(); // erases all string

		// Search
		auto pos = s.find("Sugar", 0);
		if (pos != std::string::npos) // std::string::npos is -1
		{
			std::cout << "\nfound\n";
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
		std::cout << std::stof("54") << '\n';  // string to float
		std::cout << std::stod("54") << '\n';  // string to double
		std::cout << std::stoull("54") << '\n';  // string to unsigned long long
	}

	void subroutine1() {
		//oldStyle();
		newStyle();
		//stringStream();
	}
}

namespace Assignments {
	constexpr auto fark = ('a' - 'A');
	std::string ToUpper(const std::string& str) {
		auto lenght = str.length();
		std::string temp("");
		for (size_t i = 0; i < lenght; ++i)
		{
			temp = str.at(i);
			temp = temp.c_str() + fark;
		}
		return std::string(temp);
	}
	std::string ToLower(const std::string& str) {
		auto lenght = str.length();
		std::string temp("");
		for (size_t i = 0; i < lenght; ++i)
		{
			temp = str.at(i);
			temp = temp.c_str() - fark;
		}
		return std::string(temp);
	}
	void Assignments_test() {

		std::string UP("UP");
		std::string down("down");
		ToUpper(down);
		ToLower(UP);

	}
}

void MoreCpp_Main() {
	//Enums::subroutine1();
	Strings::subroutine1();
}
