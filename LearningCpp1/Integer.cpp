#include "Integer.h"

Integer::Integer()
{
	int_ptr = new int(0);
}

Integer::Integer(int lvalue)
{
	int_ptr = new int(lvalue);
}

Integer::~Integer()
{
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
