#include <string>

#include "Account.h"

namespace Banking
{
	class Savings : public Account {
	private:
		float Rate;
	public:
		// constructor
		Savings(const std::string& name, float balance, float Rate);
		// destructor
		~Savings();

		//Member functions
		float GetInterestRate() const;
		float  AccumulateInterest();
	};

	struct Savings_TEST
	{
		void Savings_TEST1() {
			Savings savings1("Save", 100, 2);
			auto rate = savings1.GetInterestRate();
			std::cout << rate << '\n';

			auto newBalance = savings1.AccumulateInterest();
			std::cout << newBalance << '\n';

		}
		void Savings_TEST_main() {
			Savings_TEST1();
		}
	};

}