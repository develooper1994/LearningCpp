#include <iostream>
#include "Car.h"
#include "DrawLine.h"
#include "Integer.h"
#include "IntegerCpp11.h"
/*****************************************************************//**
 * \file   ClassesObjects.cpp
 * \brief  /
 - There is 4 types of programing I have ever seen. Each have both advantages and disadvantages.
 * OOPS(Object Oriented). exp: C++, Java, C#, Javascript (most mainline programing languages)
 * Imperative. exp: C, Nim languages
 * Functional. exp: Haskell, Scala
 * Declarative. exp: HTML/CSS

 - OOPS has important concepts: Abstraction, Encapsulation, Inheritance, Polymorphism
 * Abstraction(class, struct, interface, union, enum)
 *	exp: name of person without other details(age, weight, ...)
 * Encapsulation(Hides the implementation details of a class)
 * Inheritance(represents a hierarchy of classes) -> Inheritance is possible with composition
 * Polymorphism(different forms)
 *	Ways of polymorphism "at compile times": function overloading, templates and virtual

 - Class is a blueprint or a template or a recipe
 * By default access to to class members and methods are "private"

 - Constructor
 * Calls when object created
 * Used to initialize the object with user defined values.
 * Can be overloaded. Accept arguments.
 * May acquire some resources when object is created.
 - Destructor used to remove the object with user defined values.
 * Calls when object out of scope
 * Cannot overloaded.
 * Doesn't accept arguments
- Constructor types: Copy(swallow|deep) and Move
* All constructors should provided in most cases!
* Move constructor = swaps pointer addresses. (really fast)(eliminates and also leads to bugs.)
To perform deep copy create a new slot(new <type>(data)).
* Swallow copy constructor = only copy the address of variable (fast)(leads to bugs.)
* Deep copy constructor = copy the entire data (slow)(prevents some bugs.)



 - Struct is almost the same as class in c++. Only difference is access modifier is public by default.
 * Generally used as color and vector3d applications.
 * Used for function objects. Function objects used as callbacks in the STL
 Not: In Different languages Class and Struct has different meaning!
 *
 *
 *
 *
 * \author Mustafa Selcuk �a�lar
 * \date   June 2022
 *********************************************************************/

void FirstClassCar()
{
	using namespace std;
	{
		cout << "\nCalls Car::Car() constructor\n";
		Car car1, c;
		car1.Dashboard();

		car1.FillFuel(10);

		car1.Accelerate();
		car1.Accelerate();
		car1.Accelerate();
		car1.Accelerate();
		car1.Accelerate();
		car1.Accelerate();
		car1.Accelerate();

		car1.Dashboard();
	}

	{
		cout << "\nCalls Car::Car(float amount) constructor\n";
		Car::GetShowCount();
		Car car1(5), c2, c3;
		car1.Dashboard();

		//car1.FillFuel(10);

		car1.Accelerate();
		car1.Accelerate();
		car1.Accelerate();
		car1.Accelerate();
		car1.Accelerate();
		car1.Accelerate();
		car1.Accelerate();

		Car c4, c5;

		car1.Dashboard();
	}

	cout << "\nconst object creation\n";
	{
		cout << "\nCalls Car::Car(float amount) constructor\n";
		Car::GetShowCount();
		const Car car1(50), c2, c3;
		car1.Dashboard();

		Car c4, c5;

		car1.Dashboard();
	}
}

void BeautifulLines()
{
	int x1 = 1, y1 = 1, x2 = 2, y2 = 2;
	DrawTheLine(x1, y1, x2, y2);

	Point start{ 1,1 }, end{ 2,2 };
	DrawTheLine(start, end);

}

void SwallowCopy_DeepCopy_program_crashes() {
	// !!! Program may crash due to security checks(shallow copy) !!!
	// SwallowCopy
	{
		/*
		I am now coping pointers inside of the objects.It is shallow copy(coping only the address of pointer not data).
		If i change the data with some pointer, this will affect all swallow copied pointers.
		*/
		int* p1 = new int(5);
		int* p2 = p1; // coping only the address of pointer not data
	}
	// DeepCopy
	{
		// We have to define user defined copy constructor.
		int* p1 = new int(5);
		int* p2 = new int(*p1);
	}
}

void IntegerClass_SwallowCopy_program_crashes()
{	// !!! Program will crash due to security checks !!!
	using namespace std;
	Integer i(5);
	/*
	// SwallowCopy_program_crashes
	// I am now coping pointers inside of the objects. It is shallow copy(coping only the address of pointer not data). !!! Program will crash !!!
	Integer i2(i); // shallow copy constructor. Automatically created
	i = i2;	// shallow copy constructor. Automatically created
	*/

	// Integer(const Integer& obj);
	// I fixed it :]. I created custom copy constructor.
	Integer i2(i);
	cout << i.GetValue() << '\n';
}

void IntegerCpp11_func()
{
	IntegerCpp11 i1, // default constructor
		i2(3); // parameterized constructor
	// !!! Compiler Error !!!
	//IntegerCpp11 i3, // synthesized default constructor
	//	i4(i3); // forbidden(deleted) copy constructor

	i1.SetValue(10);
	// i1.SetValue(10.5f); // !!! Compiler Error !!! // float assignments deleted.

}



void ClassesObjects_Main()
{
	FirstClassCar();
	BeautifulLines();

	// Constructors
	SwallowCopy_DeepCopy_program_crashes(); // !!! Program may crash due to security checks(shallow copy) !!!
	IntegerClass_SwallowCopy_program_crashes();	// !!! Program will crash due to security checks !!!

	IntegerCpp11_func();
}
