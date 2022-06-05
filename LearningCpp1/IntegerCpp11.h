#pragma once
/*
"default" and "delete" is a special keyword. You can only use it C++11 and higher standarts.
"default" => It synthesis constructors, destructor, operators automatically if it needed.
"delete" => Forbids usage of almost anything.
*/

// copy forbidden | move allowed.
class IntegerCpp11
{
	int val{ 0 }; // If you remove manually defined default constructor, compiler can't synthesis default constructor. It needs a "default"
	//int val = 0;
public:
	/*IntegerCpp11() {
		val = 0;
	}*/
	IntegerCpp11() = default; // Compiler can generates default constructor now.
	IntegerCpp11(IntegerCpp11&&) = default; // Compiler can generates move constructor now.
	IntegerCpp11(const IntegerCpp11&) = delete; // Compiler can forbids copying the class objects. Second way to do that. make copy constructor private ;)
	IntegerCpp11(int val) {
		this->val = val;
	}
	void SetValue(int value) {
		this->val = value;
	}
	void SetValue(float value) = delete; // member is "int" i don't want to shoot from my foot. So i am deleting float assignments.
};