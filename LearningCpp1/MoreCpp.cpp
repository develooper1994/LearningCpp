#include <iostream>


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



void MoreCpp_Main() {
	Enums::subroutine1();
}
