#include "Transact.h"

namespace Banking
{
	void Transact(Account* account) // careful! base pointer!
	{
#ifdef _BANKING_DEBUG
		std::clog << __FUNCSIG__ << '\n';
#endif // _BANKING_DEBUG
		std::cout << "Transaction started\n";
		std::cout << "Initial balance:" << account->GetBalance() << '\n';

		// magic happens here!
		/*
		* Without virtual function "account" only calls base class member function.
		* Compiler generates for non virtual functions
		- "Banking::Account::Deposit"
		- "Banking::Account::AccumulateInterest"
		- "Banking::Account::WithDraw"
		//
		*/
		account->Deposit(100); // +100
		account->AccumulateInterest();
		account->WithDraw(170); // -170

		std::cout << "Interest rate:" << account->GetInterestRate() << '\n';
		std::cout << "Final balance:" << account->GetBalance() << '\n'; // balance - 30
	}
}
