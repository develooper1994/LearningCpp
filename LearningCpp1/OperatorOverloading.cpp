#include <iostream>
#include "Integer.h"
#include <memory> // smart pointers

namespace OperatorOverloading_utility_functions {
	Integer Add(const Integer& a, const Integer& b)
	{
		Integer temp;
		temp.SetValue(a.GetValue() + b.GetValue());
		return temp;
	}
}

namespace OperatorOverloading_functions {
	/*
	Associativity, precendence, arity(operator count) does not change
	Overloaded operator functinos should be non-static !!! except for new and delete !!! .

	// !!! If function parameters don't start with class name(Integer) must be global or friend !!!
	// !!! so that these operators must be global or friend. !!!

	C++ doesn't allow all the operators. exp: '.'(dot), '?'(ternary) ,'.*'(pointer to member), 'sizeof', '#'(hash), (casting operator)
	Cannot define new operator
	*/
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
			// if you define conversion operator it will compiler error. 
			// compiler doesn't know how to convert 
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

			// it is also OK!
			auto sum3 = operator+(5, a); // calls "operator+(int i, const Integer& obj)"
			std::cout << sum3 << '\n'; // ostream

			Integer c;
			std::cin >> c;  // istream
			std::cout << "c: " << c << '\n';

			// Function call opeator
			c(); // calls operator()()


		}
	}
	void SmartPointerBasics() {
		/*
		* You may heard RAII(resource acquisition is initialization). You can see in some other programing languages.
		* Smart pointer behaves like a regular pointer but it automatically frees the memory.
		* Smart pointers are reference counters. They hold a reference counter internally to free resource whenever become useless or reference counter becomes 0.
		* It is a some kind of garbage collection. It prevents most memory leaks.
		* It bounds the resources.
		* It is useful when using cyclic buffers.
		*
		* It is c++11 feature.
		*
		* !!! It may slow down operations but it is not important in most cases !!!.
		*/

		std::cout << "\n -*-*-* Situation 1  *-*-*- \n";
		{
			auto* p = new Integer; // invokes constructor
			p->SetValue(3);
			std::cout << p->GetValue() << '\n';
			delete p; // invokes destructor
		}

		std::cout << "\n -*-*-* Situation 2  *-*-*- \n";
		{
			IntPtr p = new Integer;
			//p->SetValue(3); // p.operator->()->SetValue(3);
			(*p).SetValue(3); // p.operator*().SetValue(3);

			/*std::cout << p->GetValue() << '\n';
			delete p;*/
		}

		std::cout << "\n -*-*-* unique_ptr<type> *-*-*- \n";
		// don't want to share the underlying resource
		// copy constructor deleted function.
		// you can only move the object
		{
			// I don't see the IntPtr constructor and destructor.
			std::unique_ptr<Integer> p(new Integer); // you can not copy the unique_ptr. copy constructor deleted function.
			//auto p2(p); // !!! ERROR !!!
			(*p).SetValue(3);
			std::cout << p->GetValue() << '\n';

			// print(p); // trying to copy unique pointer. Use shared_ptr
			print(std::move(p)); // std::move calls move constructor of unique_ptr
			// std::cout << p->GetValue() << '\n'; // after the move operation p will hold no longer the resource. p will be destroyed.
		}

		std::cout << "\n -*-*-* shared_ptr<type> *-*-*- \n";
		// want to share the underlying resource
		// copy constructor has reference counter.
		// reference counter increases by creating new copies, decreases by end of the scope
		{
			// I don't see the IntPtr constructor and destructor.
			std::shared_ptr<Integer> p(new Integer); // you can not copy the unique_ptr. copy constructor deleted function.
			//auto p2(p); // !!! ERROR !!!
			(*p).SetValue(3);
			std::cout << p->GetValue() << '\n';

			print(p); // std::move calls move constructor of unique_ptr
			std::cout << p->GetValue() << '\n'; // after the move operation p will hold no longer the resource. p will be destroyed.
		}

	}
}

namespace TypeConversions {
	/*
	implicit(by compiler), explicit(by programmer)
	explicit conversion uses casting operators
	* basic->basic
	* basic->user-defined
	* user-defined->basic
	* user-defined->user-defined
	*/


	void TypeConversions1() {
		int a = 3, b = 2;
		std::cout << "\n -*-*-* C style casts are discouraged(dýþlandý)  *-*-*-\n";
		// It doesn't check is it valid.
		{
			float f = a / b; // implicit not always gives the correct result.
			std::cout << "a/b: " << a / b << '\n'; // result is 1
			std::cout << "float(a) / float(b): " << float(a) / float(b) << '\n'; // result is 1.5
			std::cout << "float(a) / b: " << float(a) / b << '\n'; // result is 1.5
			std::cout << "float(a / b): " << float(a / b) << '\n'; // result is 1.0 // first calculates and then converts ;)

			const int x = 1;
			int* p = (int*)&x; // I am discarding the qualifiers. It is source of bugs.
			int* p2 = const_cast<int*>(&x); // 
		}

		std::cout << "\n -*-*-* C++ style casts are recommended  *-*-*-\n";
		// It checks is it valid.
		{
			float f = static_cast<float> (a) / b;
			std::cout << f << '\n';

			char* p = reinterpret_cast<char*>(&a); // It doesn't discarding the qualifiers. You know what you are doing. You have the responsibility.

			const int x = 1;
			int* px = (int*)&x; // I am discarding the qualifiers. It is source of bugs.
			// int* p = reinterpret_cast<int*>(&x); // !!! ERROR !!! // I cannot discarding the qualifiers.
			int* p2 = const_cast<int*>(&x); // I am discarding the qualifiers.
		}

		auto Print1 = [](Integer a) {};
		auto Print2 = [](const Integer& a) {};
		std::cout << "\n -*-*-* Primitive -> User Defined  *-*-*-\n";
		{
			Integer a1{ 1 };
			// Integer a2 = "z0rt"; //no suitable const char -> "Integer"
			/*
			 Compiler automatically uses parameterized constructor to convert primitive type into user defined type.
			 If you define parameterized constructor with "explicit" keyword, You will not use implicit conversion.
			 "explicit" keyword forbids implicit conversion!
			 ! In most cases uses it is a Recommended keyword to eliminate bugs !
			*/
			// Initialization
			Integer a2 = 2; // parameterized constructor
			Print1(5); // parameterized constructor
			Print1(5555); // parameterized constructor
			//Assignment
			a1 = 3; // R-value -> move assignment

		}

		std::cout << "\n -*-*-* User Defined -> Primitive  *-*-*-\n";
		{
			Integer a1{ 5 };
			// Initialization
			Integer a2 = 5;
			Print1(5);
			// Assignment
			a1 = 3;
			// I have to implement "operator <type>()" function
			int xi = static_cast<int>(a1); // I have defined "explicit operator int()" explicitly. I have to cast 
			long xl = a1;
			float xf = a1;
			double xd = a1;

		}

		class Complex
		{
			Integer x;
			int y;
		public:
			// Difference is constructor calls
			/*
			*  2. step is difference "Integer(const Integer& obj)" vs "Integer()"
			initializer just calls(2 function): copy constructors || second calls(3 function): default constructor -> copy constructors -> copy assignment
			* destructors steps are the same
			*/
			Complex(const Integer& x) : x(x), y(x.GetValue()) {
				// ! Use whenever it possible !
				// calls less function and correct functions to optimize process.

				/*
				Call stack
				1) Integer(int lvalue)
				2) Integer(const Integer& obj)
				3) Complex(const Integer&)
				~Integer()
				~Complex()
				~Integer()
				*/
				std::cout << "Complex(const Integer&)\n";
				//this->Complex = Complex;
			}
			//Complex(const Integer& x) //: Complex(Complex) 
			//{
			//	/*
			//	Call stack
			//	1) Integer(int lvalue)
			//	2) Integer()
			//	3) Complex(const Integer&)
			//	4) operator=(const Integer& obj) // there is an function call
			//	~Integer()
			//	~Complex()
			//	~Integer()
			//	*/
			//	std::cout << "Complex(const Integer&)\n";
			//	this->x = x;
			//	this->y = x.GetValue();
			//}
			~Complex() {
				std::cout << "~Complex()\n";
			}
		};
		std::cout << "\n -*-*-* Initialization vs Assignment  *-*-*-\n"; // tanýmlarken deðer verme || tanýmladýktan sonra deðer verme.
		{
			std::cout << "\n\tInitialization\n";
			{
				// less function call than assignment.
				Integer b(5);
				std::cout << b << '\n';
			}
			std::cout << "\n\tAssignment\n";
			Integer b;
			// Assignment
			/*
			1) calls default constructor(left side)
			2) creates temporary object and calls parameterized constructor.(right side)
			we have 2 object
			3) calls move operator.
			4) temporary objects calls destructor
			5) assignment complete
			6) second objects calls destructor
			*/
			b = 6;
			std::cout << b << '\n';
		}

		std::cout << "\n -*-*-* Initialization vs Assignment in the classes  *-*-*-\n";
		{
			// debug the two constructor and see what happens under the process.
				// Complex(const Integer& x) : x(x), y(x.GetValue())
				// ! Use whenever it possible !
				// calls less function and correct functions to optimize process.
			Complex c(5);
		}

	}
}

void OperatorOverloading_Main()
{
	//OperatorOverloading_functions::OperatorOverloading1();
	//OperatorOverloading_functions::SmartPointerBasics();

	TypeConversions::TypeConversions1();
}