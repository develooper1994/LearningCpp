#pragma once
#include "Account.h"
#include "Savings.h"
#include "Checking.h"

using namespace Banking;

void Banking_Main_Test() {
	Account_TEST accTest;
	accTest.Account_TEST_main();

	Savings_TEST saving_Test;
	saving_Test.Savings_TEST_main();


}
