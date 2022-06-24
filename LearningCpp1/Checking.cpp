#include "Checking.h"

using namespace Banking;

//Checking::Checking(const std::string& name, float accBalance)
//	: Account(name, accBalance) {
//#ifdef DEBUG
//	std::clog << __FUNCSIG__ << '\n';
//#endif // DEBUG
//	// exist only to invoke the base class constructor.
//	// It doesn't do nay initialization of its own in C++ ;)
//	/*
// 		// Call Stack with Checking constructor
//		__cdecl Banking::Account::Account(const class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > &,float)
//		__cdecl Banking::Checking::Checking(const class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > &,float)
//	*/
//}

Checking::~Checking() {
#ifdef DEBUG
	std::clog << __FUNCSIG__ << '\n';
#endif // DEBUG
}

void Checking::WithDraw(float amount, float max) {
#ifdef DEBUG
	std::clog << __FUNCSIG__ << '\n';
#endif // DEBUG
	if (std::floor(accBalance - amount) > max) {
		Account::WithDraw(amount); // Valid!
		// WithDraw(amount); // Invalid! It may call recurve
	}
	else
	{
		std::cerr
			<< "Paraniz max: " << max
			<< " degerin altinda. Yeterli para yok!\n";
	}
}
