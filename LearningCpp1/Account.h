#pragma once
#include <iostream>

//#define _BANKING_DEBUG

//#ifndef _ACCOUNT
//#define _ACCOUNT

/*
Virtual keyword help to compiler to generate correct function call
polymorphic function, that means when these functions are invoked, they will be invoked
on the correct that Account pointer is pointing at.
*/

namespace Banking
{
	class Account
	{
	private:
		std::string accName;
		int accNo;
		static int AccGenerator; // auto generated.
	protected:
		float accBalance;
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
		// generates new function bodies for each child classes
		virtual void Deposit(float amount);
		virtual void WithDraw(float amount);
		virtual void AccumulateInterest();
		virtual float GetInterestRate() const;

	};

	struct Account_TEST
	{
		inline void Account_TEST1() {
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
