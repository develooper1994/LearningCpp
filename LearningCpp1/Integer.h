#pragma once
#include <iostream>

/*
Copy constructor automatically synthesizes but compiler generates wrong(swallow) copy constructor
I have created custom(deep) copy constructor.
*/
class Integer
{
private:
	int* int_ptr;
public:
	//constructors
	Integer();
	Integer(int lvalue);
	//destructor
	~Integer();
	int GetValue() const;
	void SetValue(int value);
};

void print(Integer);
Integer add(int, int);

