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
	}

	//Getters
	const std::string Account::GetName() const
	{
		return this->accName;
	}

	float Account::GetBalance() const
	{
		return this->accBalance;
	}

	int Account::GetAccountNo() const
	{
		return this->accNo;
	}

	//Setters
	void Account::SetName(const std::string& str)
	{
		this->accName = str;
	}

	void Account::SetBalance(const float& accBalance)
	{
		this->accBalance = accBalance;
	}

	void Account::SetAccountNo(const int& accNo)
	{
		this->accNo = accNo;
	}

	//Member functoins
	void Account::AccumulateInterest() {

	}
	void Account::WithDraw(float amount) {
		if (this->accBalance < amount)
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
		this->accBalance += amount;
	}
	float Account::GetInterestRate() const {
		return 0.0f; // will be implemented at child class
	}

}