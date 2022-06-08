/*
lvalue(variable)(copy)(int&) || rvalue(value)(temporary)(move)(<type>&&)
lvalue references always bind to lvalue || rvalue references always bind to rvalue

*/

#include <iostream>
#include "Integer.h"
#include "Number.h"

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
	Number CreateNumber(int num) {
		Number n{ num };
		return n;
	}
	void move1() {
		std::cout << "\nmove1\n";
		Integer a(1), b(2);
		a.SetValue(Add(a, b).GetValue());
	}
	void move2() {
		// Try it in debug and release modes
		std::cout << "\nmove2\n";
		Number n1{ 1 };
		auto n2{ n1 };
		n2 = n1;

		auto n3{ CreateNumber(5) };
		n3 = CreateNumber(7);
	}
	void MoveStandart() {
		/* !!!RAII principle basics  !!!Why we need smart pointers ?
		std::move usages
		* I don't want to utilize those resources after the function.
		* Pass non-copyable variables to function.
		* ! usage of primitive type redundant !
		*/
		Integer a(1);
		// auto b{ static_cast<Integer&&>(a) }; // Calls move constructor, doesn't readable
		auto b{ std::move(a) }; // Same meaning as "auto b{ static_cast<Integer&&>(a) };"
		// Try it with removing Integer class copy-constructor. It will not compile!
		print(a); // pass-by-value. Underlying resource of a doesn't removed exit of print function
		// I don't want to utilize those resources after the function. 
		print(std::move(a)); // pass-by-reference. Underlying resource of a removed exit of print function.
		std::cout << "After the std::move(a) resources moved into the function. Program will crash\n"; // You are trying to read from nullptr(inside of the Integer class)


	}
	void Move_main()
	{
		//move1();
		//move2();
		MoveStandart();
	}
}

void L_R_Values_Main()
{
	//LvsRvalue::LvsR();
	LvsRvalue::Move_main();
}
