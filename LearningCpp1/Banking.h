#pragma once

#include "Account.h"
#include "Savings.h"
#include "Checking.h"

void Banking_Main_Test() {
	Banking::Account_TEST accTest;
	accTest.Account_TEST_main();

	Banking::Savings_TEST savingTest;
	savingTest.Savings_TEST_main();

	Banking::Checking_TEST checkingTest;
	checkingTest.Checking_TEST_main();
}
