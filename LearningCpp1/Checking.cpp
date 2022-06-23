#include "Checking.h"


using namespace Banking;

Checking::Checking(const std::string& name, float balance)
	: Account(name, balance)
{
}

Checking::~Checking()
{
}

void Checking::WithDraw(float amount, float max)
{
	if (std::floor(accBalance - amount) > max) {
		Account::WithDraw(amount); // Valid!
		// WithDraw(amount); // Invalid! It may call recurve
	}
	else
	{
		std::cerr << "Yeterli para yok!\n";
	}
}
