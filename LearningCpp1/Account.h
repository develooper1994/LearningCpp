#pragma once
#include <iostream>
//#ifndef _ACCOUNT
//#define _ACCOUNT


namespace Banking
{
	class Account
	{
	protected:
		std::string accName;
		float accBalance;
		int accNo;
		static int AccGenerator; // auto generated.
	public:
		// constructors
		//Account();
		Account(const std::string& name, float accBalance);
		// destructors
		~Account();

		// Getters
		const std::string GetName() const;
		float GetBalance() const;
		int GetAccountNo() const;

		//Setters
		void SetName(const std::string& str);
		void SetBalance(const float& accBalance);
		void SetAccountNo(const int& accNo);

		//Member functions
		void AccumulateInterest();
		void WithDraw(float amount);
		void Deposit(float amount);
		float GetInterestRate() const;

	};

	struct Account_TEST
	{
		void Account_TEST1() {
			Account acc1("Bob", 1000);
			std::cout << "Initial balance: " << acc1.GetBalance() << '\n';
			acc1.Deposit(200); // +200
			acc1.WithDraw(300); // -300
			std::cout << "Balance: " << acc1.GetBalance() << '\n'; // 900
		}
		void Account_TEST_main()
		{
			Account_TEST1();
		}
	};


	//#endif // !1

}
