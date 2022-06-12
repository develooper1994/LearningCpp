#pragma once
#include <memory>

// -*-*-* PrinterShared *-*-*-
class PrinterShared
{
private:
	std::shared_ptr<int> value;	// !memory leak!
public:
	void Set(std::shared_ptr<int> val);
	void Display();
};



// -*-*-* PrinterWeak *-*-*-
class PrinterWeak
{
private:
	std::weak_ptr<int> value; // prevents unnecessary refc increments.
public:
	void Set(std::shared_ptr<int> val);
	void Display();
};

