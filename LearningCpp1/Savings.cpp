#include "Savings.h"

namespace Banking
{
	Savings::Savings(const std::string& name, float balance, float Rate)
		: Account(name, balance), Rate(Rate)
	{
	}

	Savings::~Savings() {
	}

	float Savings::GetInterestRate() const {
		return Rate;
	}
	float Savings::AccumulateInterest() {
		accBalance += (accBalance * Rate);
		return accBalance;
	}
}