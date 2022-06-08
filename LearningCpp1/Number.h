#pragma once
/*
Automatically synthesized by the compiler

	Custom				Copy Constructor			Copy assignment			Move Constructor			Move assignment			Destructor
Copy constructor			CUSTOM						=default				=delete						=delete				=default
Copy assignment				=default					CUSTOM					=delete						=delete				=default
Move constructor			=delete						=delete					CUSTOM						=delete				=default
Move assignment				=delete						=delete					=delete						CUSTOM				=default
Destructor					=default					=default				=delete						=delete				CUSTOM
None						=default					=default				=default					=default			=default

Note:
copy defined => move delete
move defined => copy delete
destructor defined => move delete
none defined => everything is default
*/

/*
!!! IMPOTANT NOTE !!!
-If you don't define any of copy or move constructor and operators, compiler generates them.
-If you define any of copy, you should define all of them.
-If you define any of move, you should define all of them.
All should be defined if a user implements any of them. !Otherwise it can lead to memory leaks(or shallow copy)!
	- Destructor
	- (deep) Copy constructor
	- (deep) Copy assignment Operator => performs (deep) Copy constructor
	- Move constructor
	- Move assignment Operator => performs Move constructor
*/

/*
"Constructor Elision" or "Named return value optimization"
* Sometimes you don't see temporary objects, that is why compiler also can elide constructors to optimize software.
* Almost all compliers have this feature.
* It generally applied in RELEASE MODE.
* To use it, class should have copy and move constructors but c++17 standart changed it.
*/
#include "Integer.h"
class Number
{
private:
	Integer Value{};
public:
	Number() = default;
	Number(int val);
	// copy
	Number(const Number& obj) = default;
	Number& operator=(const Number& obj) = default; // Let the compiler synthesize automatically
	// move
	// When we provide a custom implementation of any move operation, copy operations deleted.
	//Number(Number&& obj) : Value{ std::move(obj.Value) } {}
	Number(Number&& obj) = default;
	Number& operator=(Number&& obj) = default; // Let the compiler synthesize automatically
};

