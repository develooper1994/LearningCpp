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

Integer& Integer::operator=(const Integer& obj)
{
	std::cout << "operator=(const Integer& obj)\n";
	if (int_ptr != obj.int_ptr)	// What if assign to itself.
	{
		delete int_ptr;
		int_ptr = new int(*obj.int_ptr);
	}
	return *this;
}

inline void Integer::Move(Integer& obj) {
	int_ptr = obj.int_ptr;
	obj.int_ptr = nullptr; // potential memory leak!
}

Integer::Integer(Integer&& obj)
{
	std::cout << "Integer(Integer&& obj)\n";
	Move(obj);
}

Integer& Integer::operator=(Integer&& obj)
{
	std::cout << "operator=(Integer&& obj)\n";
	if (int_ptr != obj.int_ptr)
	{
		this->Move(obj);
	}
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

// -*-*-* Operators Overloading *-*-*-
// Math
// Integer sum = a + 5;
Integer Integer::operator+(const Integer& obj) const
{
	/*
	* It is OK
	Integer a(1)
	Integer sum = a + 5;

	* It is not OK
	Integer sum = 5 + a; // needs additional integer parameter
	*/

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
// post-increment operator creates temporary objects.
Integer& Integer::operator++()
{
	// pre-increment // increment then return
	++(*int_ptr);
	return *this; // returns by reference(l-value)
}

// pre-decrement
Integer& Integer::operator--()
{
	// pre-increment // increment then return
	--(*int_ptr);
	return *this; // returns by reference(l-value)
}

// post-increment
Integer Integer::operator++(int)
{
	// post-increment // return then increment
	Integer temp(*this);
	++(*int_ptr);
	return temp; // returns by reference(l-value)
}

// post-decrement
Integer Integer::operator--(int)
{
	// post-increment // return then increment
	Integer temp(*this);
	--(*int_ptr);
	return temp; // returns by reference(l-value)
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

/*
		Function call operator. operator()
* be carreful it may cause "vexing parse problem"
It can takes as many as you want.

You can call like ...
	Integer a;
	a();
*/
void Integer::operator()() {
	std::cout << "Function call operator\n" << this->GetValue();
};




// !!! If function parameters don't start with class name(Integer) must be global or friend !!!
// !!! so that these operators must be global or friend. !!!
// Integer sum = 5 + a;
Integer operator+(int i, const Integer& obj)
{
	Integer temp;
	temp.SetValue(i + obj.GetValue());
	return temp;
}

Integer operator-(int i, const Integer& obj)
{
	Integer temp;
	temp.SetValue(i - obj.GetValue());
	return temp;
}

// operator for streaming string
// You need to #include<iosfwd>
std::ostream& operator<<(std::ostream& out, const Integer& obj) {
	// out << obj.GetValue() << '\n';
	out << *obj.int_ptr << '\n'; // only for friend functions.
	return out;
}

std::istream& operator>>(std::istream& in, Integer& obj) {
	int temp;
	in >> temp;
	// obj.SetValue(temp);
	*obj.int_ptr = temp; // only for friend functions.
	return in;
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
