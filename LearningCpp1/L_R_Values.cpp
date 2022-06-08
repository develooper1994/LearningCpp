/*
lvalue(variable)(copy)(int&) || rvalue(value)(temporary)(move)(<type>&&)
lvalue references always bind to lvalue || rvalue references always bind to rvalue

*/

#include <iostream>
#include "Integer.h"

namespace LvsRvalue {
	int Add(int x, int y) {
		return x + y;
	}
	int& Square(int& x) {
		x *= x;
		return x;
	}
	static void print(int& x) {
		std::cout << "print(int& x)\n";
	}

	static void print(const int& x) {
		std::cout << "print(const int& x)\n";
	}

	static void print(int&& x) {
		std::cout << "print(int&& x)\n";
	}
	void LvsR()
	{
		{
			int&& r1 = 10;
			int&& r2 = Add(1, 2);

			int x = 0;
			// int&& r3 = x; // !!! ERROR !!! // lvalue to lvalue
			int& r3 = x; // OK

			int& ref = Square(x);
			const int& ref2 = 1; // purpose is detect temporaries
		}

		{
			int x = 10;
			print(x);
			print(3); // if "int&& x" doesn't exist it binds to "const int& x"
		}
	}

	Integer Add(const Integer& a, const Integer& b)
	{
		Integer temp;
		temp.SetValue(a.GetValue() + b.GetValue());
		return temp;
	}
	void move1() {
		Integer a(1), b(2);
		a.SetValue(Add(a, b).GetValue());
	}
	void move2() {

	}
	void Move_main()
	{
		move1();
		move2();
	}
}

void L_R_Values_Main()
{
	LvsRvalue::LvsR();
	LvsRvalue::Move_main();
}
