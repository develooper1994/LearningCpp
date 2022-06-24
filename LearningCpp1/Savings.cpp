#include "Savings.h"

namespace Banking
{
	Savings::Savings(const std::string& name, float balance, float Rate)
		: Account(name, balance), Rate(Rate)
	{
#ifdef DEBUG
		std::clog << __FUNCSIG__ << '\n';
#endif // DEBUG
	}

	Savings::~Savings() {
#ifdef DEBUG
		std::clog << __FUNCSIG__ << '\n';
#endif // DEBUG
	}

	float Savings::GetInterestRate() const {
#ifdef DEBUG
		std::clog << __FUNCSIG__ << '\n';
#endif // DEBUG
		return Rate;
	}
	float Savings::AccumulateInterest() {
#ifdef DEBUG
		std::clog << __FUNCSIG__ << '\n';
#endif // DEBUG
		accBalance += (accBalance * Rate);
		return accBalance;
	}
}