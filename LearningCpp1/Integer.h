#pragma once
#include <iostream>

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
*/
class Integer
{
private:
	int* int_ptr;
public:
	//Constructors
	Integer();
	Integer(int lvalue);
	//copy-constructor
	Integer(const Integer& obj); // It eliminates program crashes.
	//copy-assignment operator
	Integer operator=(const Integer& obj);
	//move-constructor
	Integer(Integer&& obj);
	//move-assignment operator
	Integer operator=(Integer&& obj);
	//Destructor
	~Integer();
	int GetValue() const;
	void SetValue(int value);
};

void print(Integer);
Integer add(int, int);

