#include "Integer.h"

Integer::Integer()
{
	std::cout << "Integer()\n";
	int_ptr = new int(0);
}

Integer::Integer(int lvalue)
{
	std::cout << "Integer(int lvalue)\n";
	int_ptr = new int(lvalue);
}

Integer::Integer(const Integer& obj)
{
	std::cout << "Integer(const Integer& obj)\n";
	int_ptr = new int(*obj.int_ptr);
}

Integer Integer::operator=(const Integer& obj)
{
	std::cout << "operator=(const Integer& obj)\n";
	if (int_ptr == obj.int_ptr)
	{
		*this;
	}
	delete int_ptr;
	int_ptr = new int(*obj.int_ptr);
	return *this;
}

Integer::Integer(Integer&& obj)
{
	std::cout << "Integer(Integer&& obj)\n";
	int_ptr = obj.int_ptr;
	obj.int_ptr = nullptr;
}

Integer Integer::operator=(Integer&& obj)
{
	std::cout << "operator=(Integer&& obj)\n";
	if (int_ptr == obj.int_ptr)
	{
		return *this;
	}
	int_ptr = obj.int_ptr;
	obj.int_ptr = nullptr;
	return *this;
}

Integer::~Integer()
{
	std::cout << "~Integer()\n";
	delete int_ptr;
}

int Integer::GetValue() const
{
	return *int_ptr;
}

void Integer::SetValue(int value)
{
	*int_ptr = value;
}



// Dummy functions
void print(Integer i)
{
	// copy constructor at input
	std::cout << i.GetValue() << '\n';
}
Integer add(int x, int y) {
	// copy constructor at output
	return Integer(x + y);
}
