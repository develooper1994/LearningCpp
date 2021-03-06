#pragma once
#include <string>

#include "Account.h"

namespace Banking
{
	class Savings : public Account {
	private:
		// Savings has an attribute to initialize 
		// so that we will have to implement a constructor that will initialize this attribute.
		float Rate;
	public:
		// constructor
		Savings(const std::string& name, float balance, float Rate);
		// destructor
		~Savings();

		//Member functions
		void AccumulateInterest();
		float GetInterestRate() const;
	};

	struct Savings_TEST {
		inline void Savings_TEST1() {
			Savings savings1("Save", 100, 2);
			auto rate = savings1.GetInterestRate();
			std::cout << rate << '\n';

			savings1.AccumulateInterest();
			auto newBalance = savings1.GetInterestRate();
			std::cout << newBalance << '\n';

		}
		void Savings_TEST_main() {
			Savings_TEST1();
		}
	};

}