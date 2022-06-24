#include "Account.h"
#include <string>
#include <random>
#include <iostream>

namespace Banking
{
	int Account::AccGenerator = 1000;
	// constructors
	Account::Account(const std::string& name, float accBalance)
		: accName{ name }, accBalance{ accBalance }
	{
#ifdef _BANKING_DEBUG
		std::clog << __FUNCSIG__ << '\n';
#endif // _BANKING_DEBUG

		std::default_random_engine engine;
		std::uniform_int_distribution<int> distribution(1, 10);
		auto generator = [&engine, &distribution]
		{
			return distribution(engine);
		};
		accNo = generator(); // ++AccGenerator;
	}

	// destructors
	Account::~Account()
	{
#ifdef _BANKING_DEBUG
		std::clog << __FUNCSIG__ << '\n';
#endif // _BANKING_DEBUG
	}

	//Getters
	const std::string Account::GetName() const
	{
#ifdef _BANKING_DEBUG
		std::clog << __FUNCSIG__ << '\n';
#endif // _BANKING_DEBUG
		return this->accName;
	}

	float Account::GetBalance() const
	{
#ifdef _BANKING_DEBUG
		std::clog << __FUNCSIG__ << '\n';
#endif // _BANKING_DEBUG
		return this->accBalance;
	}

	int Account::GetAccountNo() const
	{
#ifdef _BANKING_DEBUG
		std::clog << __FUNCSIG__ << '\n';
#endif // _BANKING_DEBUG
		return this->accNo;
	}

	//Setters
	void Account::SetName(const std::string& str)
	{
#ifdef _BANKING_DEBUG
		std::clog << __FUNCSIG__ << '\n';
#endif // _BANKING_DEBUG
		this->accName = str;
	}

	void Account::SetBalance(const float& accBalance)
	{
#ifdef _BANKING_DEBUG
		std::clog << __FUNCSIG__ << '\n';
#endif // _BANKING_DEBUG
		this->accBalance = accBalance;
	}

	void Account::SetAccountNo(const int& accNo)
	{
#ifdef _BANKING_DEBUG
		std::clog << __FUNCSIG__ << '\n';
#endif // _BANKING_DEBUG
		this->accNo = accNo;
	}

	//Member functions
	void Account::AccumulateInterest() {
#ifdef _BANKING_DEBUG
		std::clog << __FUNCSIG__ << '\n';
#endif // _BANKING_DEBUG
	}
	void Account::WithDraw(float amount) {
		if (this->accBalance > amount)
		{
			this->accBalance -= amount;
		}
		else
		{
			std::cerr << "Yeterli para yok!\n";
			return;
		}
	}
	void Account::Deposit(float amount) {
#ifdef _BANKING_DEBUG
		std::clog << __FUNCSIG__ << '\n';
#endif // _BANKING_DEBUG
		this->accBalance += amount;
	}
	float Account::GetInterestRate() const {
#ifdef _BANKING_DEBUG
		std::clog << __FUNCSIG__ << '\n';
#endif // _BANKING_DEBUG
		return 0.0f; // will be implemented at child class
	}

}