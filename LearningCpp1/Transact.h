#pragma once
#include "Account.h"
#include "Savings.h"
#include "Checking.h"
/*
Base class object and reference can point to any of its child class objects!
// --**--
Virtual keyword help to compiler to generate correct function call
polymorphic function, that means when these functions are invoked, they will be invoked
on the correct that Account pointer is pointing at.

*/
namespace Banking
{
	//void Transact(Checking* account);
	void Transact(Account* account);

	struct Transact_TEST
	{
		inline void Transact_TEST_Account() {
#ifdef _BANKING_DEBUG
			std::clog << __FUNCSIG__ << '\n';
#endif // _BANKING_DEBUG
			Account acc("Mustafa_Account", 100);
			Transact(&acc);
		}
		inline void Transact_TEST_Checking() {
#ifdef _BANKING_DEBUG
			std::clog << __FUNCSIG__ << '\n';
#endif // _BANKING_DEBUG
			Checking acc("Mustafa_Checking", 100);
			Transact(&acc);
		}
		inline void Transact_TEST_Savings() {
#ifdef _BANKING_DEBUG
			std::clog << __FUNCSIG__ << '\n';
#endif // _BANKING_DEBUG
			Savings acc("Mustafa_Savings", 100, 0.8f); // very attractive interest :]
			Transact(&acc);
		}
		void Transact_TEST_main() {
			Transact_TEST_Account();
			Transact_TEST_Checking();
			Transact_TEST_Savings();
		}
	};
}