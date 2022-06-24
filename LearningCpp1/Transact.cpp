#include "Transact.h"

// We should avoid using typeid and dynamic_cast, because for these operators to work, 
// the compiler had to add extra information to the polymorphic classes
// RTTI will impose overhead on the program(especially dynamic_cast)
#include <typeinfo>

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
		/*
		* I want to check balance before WithDraw if class is checking ,otherwise don't
		//What is the minimum balance of the checking account?
		//minimum balance is inside of the checking function
		// ! need a "down-casting"
		// !!! Transact_pointer exposed to the child classes. Not a good design !!!
		Checking* check1 = static_cast<Checking*>(account);
		//blind down-casting shows rate at savings class and in some cases program will be crash.
		// We need RTTI(run time type information)
		std::cout << "Minimum balance of checking:" << check1->GetMinimumBalance() << '\n';
		*/

		/*
		* I want to check balance before WithDraw if class is checking ,otherwise don't
		* I don't need it any more with dynamic_cast
		//if (typeid(*account) == typeid(Checking)) // minimumBalance info inside of Checking class. I don't want to lose it!
		//{
		//	Checking* check1 = static_cast<Checking*>(account);
		//	std::cout << "Minimum balance of checking:" << check1->GetMinimumBalance() << '\n';
		//}
		*/

		// * I want to check balance before WithDraw if class is checking ,otherwise don't
		// * slower than typeid
		Checking* check1 = dynamic_cast<Checking*>(account);
		if (check1 != nullptr) {
			std::cout << "Minimum balance of checking:" << check1->GetMinimumBalance() << '\n';
		}


		account->WithDraw(170); // -170

		std::cout << "Interest rate:" << account->GetInterestRate() << '\n';
		std::cout << "Final balance:" << account->GetBalance() << '\n';
	}
	void Transact(Account& account) // careful! base pointer!
	{
#ifdef _BANKING_DEBUG
		std::clog << __FUNCSIG__ << '\n';
#endif // _BANKING_DEBUG
		std::cout << "Transaction started\n";
		std::cout << "Initial balance:" << account.GetBalance() << '\n';

		// magic happens here!
		/*
		* Without virtual function "account" only calls base class member function.
		* Compiler generates for non virtual functions
		- "Banking::Account::Deposit"
		- "Banking::Account::AccumulateInterest"
		- "Banking::Account::WithDraw"
		//
		*/
		account.Deposit(100); // +100
		account.AccumulateInterest();
		/*
		* I want to check balance before WithDraw if class is checking ,otherwise don't
		//What is the minimum balance of the checking account?
		//minimum balance is inside of the checking function
		// ! need a "down-casting"
		// !!! Transact exposed to the child classes. Not a good design !!!
		Checking* check1 = static_cast<Checking*>(account);
		//blind down-casting shows rate at savings class and in some cases program will be crash.
		// We need RTTI(run time type information)
		std::cout << "Minimum balance of checking:" << check1->GetMinimumBalance() << '\n';
		*/

		/*
		* I want to check balance before WithDraw if class is checking ,otherwise don't
		* I don't need it any more with dynamic_cast
		//if (typeid(*account) == typeid(Checking)) // minimumBalance info inside of Checking class. I don't want to lose it!
		//{
		//	Checking* check1 = static_cast<Checking*>(account);
		//	std::cout << "Minimum balance of checking:" << check1->GetMinimumBalance() << '\n';
		//}
		*/

		// * I want to check balance before WithDraw if class is checking ,otherwise don't
		// * slower than typeid
		Checking& check1 = dynamic_cast<Checking&>(account); // dynamic_cast reference throws "bad_cast" exception
		//if (check1 != nullptr) // reference cannot be null
		std::cout << "Minimum balance of checking:" << check1.GetMinimumBalance() << '\n';



		account.WithDraw(170); // -170

		std::cout << "Interest rate:" << account.GetInterestRate() << '\n';
		std::cout << "Final balance:" << account.GetBalance() << '\n';
}
}
