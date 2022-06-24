#include "Savings.h"

namespace Banking
{
	Savings::Savings(const std::string& name, float balance, float Rate)
		: Account(name, balance), Rate(Rate)
	{
#ifdef _BANKING_DEBUG
		std::clog << __FUNCSIG__ << '\n';
#endif // _BANKING_DEBUG
	}

	Savings::~Savings() {
#ifdef _BANKING_DEBUG
		std::clog << __FUNCSIG__ << '\n';
#endif // _BANKING_DEBUG
	}

	float Savings::GetInterestRate() const {
#ifdef _BANKING_DEBUG
		std::clog << __FUNCSIG__ << '\n';
#endif // _BANKING_DEBUG
		return Rate;
	}
	void Savings::AccumulateInterest() {
#ifdef _BANKING_DEBUG
		std::clog << __FUNCSIG__ << '\n';
#endif // _BANKING_DEBUG
		//accBalance += (accBalance * Rate);
		//accBalance = accBalance * (Rate + 1);
		accBalance *= (Rate + 1); // some math operations happend
	}
}