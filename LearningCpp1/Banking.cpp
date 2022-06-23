#include "Banking.h"

namespace Banking
{
	void Banking_Main_Test() {
		Account_TEST accTest;
		accTest.Account_TEST_main();

		Savings_TEST savingTest;
		savingTest.Savings_TEST_main();

		Checking_TEST checkingTest;
		checkingTest.Checking_TEST_main();
	}
}