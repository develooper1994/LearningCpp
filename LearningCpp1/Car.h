#pragma once
#include "AllStandartHeaders.h"

/*
* "auto" is not allows in class member declarations.
*
* Initialization from class member declaration is only for non-static and basic types and simple values.
* For more sophisticated initialization, You must use constructor.
*
* this pointer only has meaning inside of class. It stores "Class Address" in the memory. It is optional. Compiler implicitly embeds it.
* Every function call in assembly call with "lea(load effective address)"
* This increases readability in some cases and help to compiler.
* Most important use case is "this pointer" is that it is a good argument when using class as a function or method input and output argument. Use it with dereference.
*

Static
* Static Members have to initialized outside of the class.
declare like that => static int ClassCreationCount;
initialize like that => int Car::ClassCreationCount = 0;

Static Member Functions:
* !!! Do not receive this pointer so that Cannot access non-static members of the class !!!!
* !!! Can be invoked directly through the class name without creating the class !!!
* Belong to the class not object(created class)
*

Const object creation
* If you don't provide const methods code will not compile
* After the function const means "I am not going to change anything. I am going to just read the data. I promise!"
* All the member functions that don't modify the state of the object should be qualified with the const keyword.
* If you try the change any member variable inside const function, compiler complains about that.
* exp: void Dashboard() const;

*
*
*
*
*/

class Car
{
private:
	float fuel{ 0 };
	float speed{ 0 };
	int passengers{ 0 };
	std::array<int, 5> seats_unoccupied{ 0,1,2,3,4 };
	char* plate{}; // default value is NULL
	// auto i = 5; // !!! Error !!!
	static int ClassCreationCount; // static members have to initialized outside of the class.
public:
	// Constructors
	Car();
	Car(float amount);
	Car(float amount, int pass);
	// Destructors
	~Car();
	//Methods
	void SetDefaults(); // uninitialized variables gives random and strange results;
	void FillFuel(float litre);
	void Accelerate();
	void Brake();
	void AddPassengers(int passengers);
	void Dashboard() const;
	//Static Member Functions
	static void GetShowCount();
};