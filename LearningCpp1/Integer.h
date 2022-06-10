#pragma once
#include <iostream>
#include <iosfwd>

#include <memory>

/*
Copy constructor automatically synthesizes but compiler generates wrong(swallow) copy constructor
I have created custom(deep) copy constructor.
	//copy-constructor
	// If you pass object by value(not with reference) then again copy of object will get created and that would invoke the constructor again.
	// const keyword not mandatory however I can avoid modification with it.
	// In most cases when objects passed by reference into functions, they are always qualified with const.

!!! IMPOTANT NOTE !!!
All should be defined if a user implements any of them. !Otherwise it can lead to memory leaks(or shallow copy)!
	- Destructor
	- (deep) Copy constructor
	- (deep) Copy assignment Operator => performs (deep) Copy constructor
	- Move constructor
	- Move assignment Operator => performs Move constructor

-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

!!! IMPOTANT NOTE !!!
All should be defined if a user implements any of them. !Otherwise it can lead to compiler errors!
	- Conversion operators
	- Math and other(like comparison) operators(operator+(const <class>&), operator+(<type>, const <tpye>&), operator-(const <class>&), operator-(<type>, const <tpye>&), ...)

*/
class Integer
{
private:
	int* int_ptr;
	void Move(Integer& obj);
public:
	//Constructors
	Integer();
	// parameterized constructor
	Integer(int lvalue);
	//copy-constructor
	Integer(const Integer& obj); // It eliminates program crashes.
	//copy-assignment operator
	Integer& operator=(const Integer& obj);
	//move-constructor
	Integer(Integer&& obj);
	//move-assignment operator
	Integer& operator=(Integer&& obj);
	//Destructor
	~Integer();
	int GetValue() const;
	int* GetPointer() const;
	void SetValue(int value);

	// -*-*-* Operators Overloading *-*-*-
	// Math
	// Integer sum = a + 5;
	Integer operator+(const Integer& obj) const; // doesn't modify the state of the object, so qualify it with const.
	Integer operator+(const int& obj) const; // I have to define if I define "operator int()"
	Integer operator-(const Integer& obj) const; // doesn't modify the state of the object, so qualify it with const.
	Integer operator-(const int& obj) const; // I have to define if I define "operator int()"

	// Increment - Decrement
	Integer& operator++(); // pre-increment // increment then return
	Integer& operator--(); // pre-increment // increment then return
	Integer operator++(int); // post-increment // return then increment
	Integer operator--(int); // post-increment // return then increment

	// Comparison
	bool operator==(const Integer& obj) const;
	bool operator==(const int& i) const;
	bool operator<(const Integer& obj) const;
	bool operator<(const int& i) const;
	bool operator<=(const Integer& obj) const;
	bool operator<=(const int& i) const;
	bool operator>(const Integer& obj) const;
	bool operator>(const int& i) const;
	bool operator>=(const Integer& obj) const;
	bool operator>=(const int& i) const;

	/*
			Function call operator. operator()
	* be carreful it may cause "vexing parse problem"
	It can takes as many as you want.

	You can call like ...
		Integer a;
		a();
	*/
	void operator()();

	// Conversion operator
	// I define any of them, i have to define math operator.
	// int conversion -> const int& math and other operation(like comparison).
	explicit operator int(); // ! In most cases uses it is a Recommended keyword to eliminate bugs !
	operator long();
	operator long long();
	operator float();
	operator double();

	// I can access underlying pointer
	int* operator->();
	//I can call like a regular pointer
	int operator*();

	// !!! If function parameters don't start with class name(Integer) must be global or friend !!!
	// !!! so that these operators must be global or friend. !!!

	// Friend allows us to access the internal private data of the class directly.
	// so that it can source of bugs. 
	// That is why friend functions and classes should be used only as a [last resort](son çare) to solve your problem.

	// Integer sum = 5 + a;
	friend Integer operator+(int i, const Integer& obj);
	friend Integer operator-(int i, const Integer& obj);

	// operator for streaming string
	// You need to #include<iosfwd>
	friend std::ostream& operator<<(std::ostream& out, const Integer& obj);

	friend std::istream& operator>>(std::istream& in, Integer& obj);
	friend class foo; // friend class
};

class foo {

};


// 
class IntPtr
{
	Integer* ptr;
public:
	IntPtr(Integer* p) : ptr{ p } {
		std::cout << "IntPtr(Integer* p)\n";
	}
	~IntPtr() {
		/*
		* Creation and destruction order.
		Integer()
		IntPtr(Integer* p)
		~IntPtr
		~Integer()
		*/
		std::cout << "~IntPtr\n";
		delete ptr; // destructor calls Integer destructor so that there is no memory leak.
	}

	// I can access underlying pointer
	Integer* operator->() {
		return ptr; // return underlying pointer to access internal members and functions of Integer class
	}

	//I can call like a regular pointer
	Integer& operator*() {
		return *ptr;
	}
};










// Dummy functions
void print(Integer);
void print(std::unique_ptr<Integer>);
void print(std::shared_ptr<Integer>);
Integer add(int, int);

