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
	if (int_ptr == nullptr)
	{
		// object moved somewhere else and move constructor called. "std::move" is one of reason.
		int_ptr = new int{};
	}
	*int_ptr = value;
}

Integer Integer::operator+(const Integer& obj) const
{
	Integer temp;
	*temp.int_ptr = *int_ptr + *obj.int_ptr;
	return temp;
}

Integer Integer::operator-(const Integer& obj) const
{
	Integer temp;
	*temp.int_ptr = *int_ptr - *obj.int_ptr;
	return temp;
}

// pre-increment more efficient than post-increment
// post increment operator creates temporary objects.
Integer& Integer::operator++()
{
	// pre-increment // increment then return
	++(*int_ptr);
	return *this; // returns by reference(l-value)
}

Integer Integer::operator++(int)
{
	// post-increment // return then increment
	Integer temp(*this);
	++(*int_ptr);
	return temp;
}

bool Integer::operator==(const Integer& obj) const
{
	return *int_ptr == *obj.int_ptr;
}

bool Integer::operator<(const Integer& obj) const
{
	return *int_ptr < *obj.int_ptr;
}

bool Integer::operator<=(const Integer& obj) const
{
	return *int_ptr <= *obj.int_ptr;
}

bool Integer::operator>(const Integer& obj) const
{
	return *int_ptr > *obj.int_ptr;
}

bool Integer::operator>=(const Integer& obj) const
{
	return *int_ptr >= *obj.int_ptr;
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
