#include "Account.h"

namespace Banking
{
	class Checking : public Account
	{
	private:
	public:
		// this will be cause all the constructor of the base to be inherited in the checking class
		// it will be similar to the manual implementation of the Checking constructor that had done earlier.
		using Account::Account;
		//constructor
		Checking(const std::string& name, float balance);
		//destructor
		~Checking();

		//member functions
		void WithDraw(float amount, float max = 50.0f);

	};

	struct Checking_TEST
	{
		void Checking_TEST1() {
			Checking checking("Bob", 1000);
			std::cout << "Initial balance: " << checking.GetBalance() << '\n';
			checking.Deposit(200); // +200
			checking.WithDraw(300); // -300
			std::cout << "Balance: " << checking.GetBalance() << '\n'; // 900
		}
		void Checking_TEST_main() {
			Checking_TEST1();
		}
	};

}