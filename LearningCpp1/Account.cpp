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
#ifdef DEBUG
		std::clog << __FUNCSIG__ << '\n';
#endif // DEBUG

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
#ifdef DEBUG
		std::clog << __FUNCSIG__ << '\n';
#endif // DEBUG
	}

	//Getters
	const std::string Account::GetName() const
	{
#ifdef DEBUG
		std::clog << __FUNCSIG__ << '\n';
#endif // DEBUG
		return this->accName;
	}

	float Account::GetBalance() const
	{
#ifdef DEBUG
		std::clog << __FUNCSIG__ << '\n';
#endif // DEBUG
		return this->accBalance;
	}

	int Account::GetAccountNo() const
	{
#ifdef DEBUG
		std::clog << __FUNCSIG__ << '\n';
#endif // DEBUG
		return this->accNo;
	}

	//Setters
	void Account::SetName(const std::string& str)
	{
#ifdef DEBUG
		std::clog << __FUNCSIG__ << '\n';
#endif // DEBUG
		this->accName = str;
	}

	void Account::SetBalance(const float& accBalance)
	{
#ifdef DEBUG
		std::clog << __FUNCSIG__ << '\n';
#endif // DEBUG
		this->accBalance = accBalance;
	}

	void Account::SetAccountNo(const int& accNo)
	{
#ifdef DEBUG
		std::clog << __FUNCSIG__ << '\n';
#endif // DEBUG
		this->accNo = accNo;
	}

	//Member functions
	void Account::AccumulateInterest() {
#ifdef DEBUG
		std::clog << __FUNCSIG__ << '\n';
#endif // DEBUG
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
#ifdef DEBUG
		std::clog << __FUNCSIG__ << '\n';
#endif // DEBUG
		this->accBalance += amount;
	}
	float Account::GetInterestRate() const {
#ifdef DEBUG
		std::clog << __FUNCSIG__ << '\n';
#endif // DEBUG
		return 0.0f; // will be implemented at child class
	}

}