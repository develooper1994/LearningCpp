#include "Banking.h"

namespace Banking
{
	void Banking_Main_Test() {
		std::cout << "\n-*-*-*-*-* " << "Account_TEST" << " *-*-*-*-*-\n\n";
		Account_TEST accTest;
		accTest.Account_TEST_main();

		std::cout << "\n-*-*-*-*-* " << "Savings_TEST" << " *-*-*-*-*-\n\n";
		Savings_TEST savingTest;
		savingTest.Savings_TEST_main();

		std::cout << "\n-*-*-*-*-* " << "Checking_TEST" << " *-*-*-*-*-\n\n";
		Checking_TEST checkingTest;
		checkingTest.Checking_TEST_main();

		std::cout << "\n-*-*-*-*-* " << "Transact_TEST" << " *-*-*-*-*-\n\n";
		Transact_TEST transactTEST;
		transactTEST.Transact_TEST_main();
	}
}