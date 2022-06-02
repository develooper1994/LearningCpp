// LearningCpp1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <bitset>
#include <math.h>
#include <complex>
#include <limits>
#include <inttypes.h>

#include <ctime>
#include <stdlib.h>

#include <array>
#include <vector>

#define NEWLINE std::cout << std::endl

void settings() {
	std::srand(std::time(nullptr));
}

void helloWorld() {
	std::cout << "Hello World!\n Mustafa Selçuk";
}

void comments() {
	// Tek satýrlýk yorum
	/*
	   Çok
	   satýrlý
	   yorum
	*/
}

void ascii() {
	NEWLINE;
	for (size_t i = 32; i < 126; ++i)
	{
		std::cout << i << ((i % 16 == 15) ? '\n' : ' ');
	}
	NEWLINE;
	NEWLINE;

	std::cout << "Printable ASCII [] \n";
	for (char i = ' '; i < '~'; ++i)
	{
		std::cout << i << ((i % 16 == 15) ? '\n' : ' ');
	}
	NEWLINE;
	NEWLINE;

	for (size_t i = 32; i < 126; ++i)
	{
		std::cout << char(i) << ((i % 16 == 15) ? '\n' : ' ');
	}
	NEWLINE;
	NEWLINE;
}

void BasicTypes() {
	std::cout << "Bare bone types \n";
	std::cout << "char: " << "min=" << std::numeric_limits<char>::min() << " " << "max=" << std::numeric_limits<char>::max() << "\n";
	std::cout << "bool: " << "min=" << std::numeric_limits<bool>::min() << " " << "max=" << std::numeric_limits<bool>::max() << "\n";
	std::cout << "int: " << "min=" << std::numeric_limits<int>::min() << " " << "max=" << std::numeric_limits<int>::max() << "\n";
	std::cout << "float: " << "min=" << std::numeric_limits<float>::min() << " " << "max=" << std::numeric_limits<float>::max() << "\n";
	std::cout << "double: " << "min=" << std::numeric_limits<double>::min() << " " << "max=" << std::numeric_limits<double>::max() << "\n";

	std::cout << "\nBare bone signed types \n";
	std::cout << "short int: " << "min=" << std::numeric_limits<short int>::min() << " " << "max=" << std::numeric_limits<short int>::max() << "\n";
	std::cout << "signed int: " << "min=" << std::numeric_limits<signed int>::min() << " " << "max=" << std::numeric_limits<signed int>::max() << "\n";
	std::cout << "long int: " << "min=" << std::numeric_limits<long int>::min() << " " << "max=" << std::numeric_limits<long int>::max() << "\n";
	std::cout << "long long int: " << "min=" << std::numeric_limits<long long int>::min() << " " << "max=" << std::numeric_limits<long long int>::max() << "\n";

	std::cout << "\nBare bone signed types \n";
	std::cout << "unsigned short int: " << "min=" << std::numeric_limits<unsigned short int>::min() << " " << "max=" << std::numeric_limits<unsigned short int>::max() << "\n";
	std::cout << "unsigned int: " << "min=" << std::numeric_limits<unsigned int>::min() << " " << "max=" << std::numeric_limits<unsigned int>::max() << "\n";
	std::cout << "unsigned short int: " << "min=" << std::numeric_limits<unsigned long int>::min() << " " << "max=" << std::numeric_limits<unsigned long int>::max() << "\n";
	std::cout << "unsigned long long int: " << "min=" << std::numeric_limits<unsigned long long int>::min() << " " << "max=" << std::numeric_limits<unsigned long long int>::max() << "\n";
}

void OutputInput() {
	int age;
	std::cout << "What is your age\n";
	std::cin >> age;
	std::cerr << "\nYour age is: " << age;
	std::clog << "\nSome logging\n";


	char name[512];
	std::cout << "What is your name\n";
	std::cin.getline(name, 15);
	std::cout << "Your name is " << name << "\n";
}

void LoopFor() {
	std::vector<int> a;
	for (size_t i = 0; i < 5; ++i)
	{
		int rand_temp = std::rand();
		a.push_back(rand_temp);
		std::cout << a.at(i) << "\n";
	}
}
void loopWhile() {
	std::array<std::array<int, 6>, 6> myarray;
	for (size_t i = 0; i < myarray.size(); i++)
	{
		myarray[i].fill(i);
	}

	int myArray_outter_size = myarray.size();
	int myArray_inner_size = myarray[0].size();

	uint8_t x = 0, y = 0;
	int	trace = 0;
	float normal = 0;
	while (x < myArray_outter_size)
	{
		auto& tempx = myarray.at(x);
		while (y < myArray_inner_size)
		{
			auto& tempxy = tempx.at(y);

			normal += tempxy;

			if (x == y)
			{
				trace += tempxy;
				y = 0;
				break;
			}
			++y;
		}
		++x;
	}

	std::cout << "trace= " << trace << "||" << "normal= " << normal << "\n";

	// do-while
	x = 0; y = 0;
	trace = 0;
	normal = 0;
	do
	{
		auto& tempx = myarray.at(x);
		do
		{
			auto& tempxy = tempx.at(y);

			normal += tempxy;

			if (x == y)
			{
				trace += tempxy;
				y = 0;
				break;
			}
			++y;
		} while (y < myArray_inner_size);
		++x;
	} while (x < myArray_outter_size);

	std::cout << "trace= " << trace << "||" << "normal= " << normal << "\n";
}
void fibonacciExercise()
{
	// call function from another file
	int n = 10;
	fibonacci_series(n);
	fib_power(n);
}

void Operators()
{
	std::cout << "\nc++ ve ++c farki\n";
	int c = 5;
	int y = c++;
	std::cout << "c= " << c << "\n";
	std::cout << "y= " << y << "\n";
	y = ++c;
	std::cout << "c= " << c << "\n";
	std::cout << "y= " << y << "\n";

	//
	std::cout << "\nc++ ve ++c farký\n";
}


#include "MyMath.h"

int main()
{
	settings();
	// helloWorld();
	// comments();
	// ascii();
	// BasicTypes();
	// OutputInput();

	// loops
	// LoopFor();
	// loopWhile();
	// Operators();
	fibonacciExercise();


	return 0;
}
























// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
