#include <iostream>
#include "Integer.h"
#include <memory>
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
		{
			++result;
			std::cout << "pre-increment: " << result.GetValue() << '\n';
			result++;
			std::cout << "post-increment: " << result.GetValue() << '\n';
		}

		// Comparisation
		{
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

		//Assignment
		{
			Integer a(1), b(2);
			b = a;
			a = a; // not valid if it address check not applied
		}

		// Global operator overloading
		{
			auto sum0 = a + 5; // calls "operator+(const Integer& obj)"
			std::cout << sum0.GetValue() << '\n';

			// it is also OK!
			auto sum1 = a.operator+(5);
			std::cout << sum1.GetValue() << '\n';

			// but Why not working?
			// cannot call "operator+(const Integer& obj)" needs additional integer parameter  aaaand
			// there is not "operator<<" and "operator>>" now
			auto sum2 = 5 + a;
			std::cout << sum2 << '\n'; // ostream
			// std::cout << ... calls
			// ...

			Integer c;
			std::cin >> c;  // istream
			std::cout << "c: " << c << '\n';

			// Function call opeator
			c(); // calls operator()()


		}
	}

	void SmartPointerBasics() {
		/*
		* You may heard RAII(resource acquisition is initialization)
		* Smart pointers are reference counters. They hold a reference counter internally to free resource whenever become useless or reference counter becomes 0.
		* It is a some kind of garbage collection.
		* It is useful when using cyclic buffers.
		*/


	}
}

void OperatorOverloading_Main()
{
	//OperatorOverloading_functions::OperatorOverloading1();
	OperatorOverloading_functions::SmartPointerBasics();

}