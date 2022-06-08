#include <iostream>
#include "Integer.h"

/*
*/

namespace OperatorOverloading_utility_functions {
	Integer Add(const Integer& a, const Integer& b)
	{
		Integer temp;
		temp.SetValue(a.GetValue() + b.GetValue());
		return temp;
	}
}

namespace OperatorOverloading_functions {
	void OperatorOverloading1() {
		Integer a(1), b(2);
		// a.SetValue(OperatorOverloading_utility_functions::Add(a, b).GetValue()); // Old and unreadable
		// Operator overloading is just syntactic sugar. Look to disassembly!
		Integer result = a + b; //Operator Already overloaded
		std::cout << result.GetValue() << '\n';

		// Increment 
		// pre-increment more efficient than post-increment
		// post increment operator creates temporary objects.
		++result;
		std::cout << "pre-increment: " << result.GetValue() << '\n';
		result++;
		std::cout << "post-increment: " << result.GetValue() << '\n';

		// Comparisation
		auto result2 = (a == b);
		std::cout << "operator== : " << result2 << '\n';

		auto result3 = (a < b);
		std::cout << "operator< : " << result3 << '\n';

		auto result4 = (a <= b);
		std::cout << "operator<= : " << result4 << '\n';

		auto result5 = (a > b);
		std::cout << "operator> : " << result5 << '\n';

		auto result6 = (a >= b);
		std::cout << "operator>= : " << result6 << '\n';

	}
}

void OperatorOverloading_Main()
{
	OperatorOverloading_functions::OperatorOverloading1();
}