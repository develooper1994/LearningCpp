#include <iostream>
#include "Printer.h"

// -*-*-* PrinterShared *-*-*-
void PrinterShared::Set(std::shared_ptr<int> val) {
	value = val;
}

void PrinterShared::Display() {
	// cannot check pointer is double deleted and valid(NULL) without smart pointer inside of function.
#if _DEBUG
	std::cout << "PrinterShared Reference Counter: " << value.use_count() << '\n';
#endif
	std::cout << "Value is: " << *this->value << '\n';
}





// -*-*-* PrinterWeak *-*-*-
// underlying pointer is std::weak_ptr ;)
//void PrinterWeak::Set(std::weak_ptr<int> val) { // if (*p > 10) !!! value.expired() == true !!!
void PrinterWeak::Set(std::shared_ptr<int> val) { // if (*p > 10) !!! value.expired() == true !!!
	value = val;
}

void PrinterWeak::Display() {
#if _DEBUG
	std::cout << "PrinterWeak Reference Counter: " << value.use_count() << '\n';
#endif
	//check if it is still valid
	if (value.expired()) {
		std::cout << "Resource is no longer available\n";
		return;
	}
	auto shared_pointer = value.lock(); // return shared_pointer. refc incremented by one
	std::cout << "Value is: " << *shared_pointer << '\n';
#if _DEBUG
	std::cout << "PrinterWeak Reference Counter: " << value.use_count() << '\n';
#endif
}