#pragma once
#include "Account.h"
#include "Savings.h"
#include "Checking.h"
/*
* virtual keyword is a runtime-time-polymorphism(dynamic)(should be invoked only through a pointer or reference)
* template keyword is a compile-time-polymorphism(static)(all but there is catch)

Base class object and reference can point to any of its child class objects!
// --**--
Virtual keyword help to compiler to generate correct function call
polymorphic function, that means when these functions are invoked, they will be invoked
on the correct that Account pointer is pointing at.


-*-*-* Virtual(runtime overload) *-*-*-
holds every virtual functions with the same name at the "VTABLE"
"Virtual Pointer" call from "VTABLE"
* Virtual Pointer will be inherited to child classes.
* To do that compiler generates some extra code.
* It may slow down and increase size of created object application in rare cases.
Note: There is some tricks to eliminate that! devirtualization, internal-linkage, override-final keywords.
But not all compilers support all of them :(

1) Get the object address
2) Get the virtual pointer
3) Find the position of the function in VTABLE
4) Get the address of the function
5) Invoke the function
Note: compilers evolved in the last years. Even in unoptimized code generates better(different) assembly!

Note: If you allocate memory dynamically be careful at destructor!
we ant is the call to destructor should be generated based
on the type of the object that the account pointer is pointing at.
For this reason, we have to make "destructor of the base class virtual".


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
		inline void Transact_TEST_destructor() {
			/*
			Note: If you allocate memory dynamically be careful at destructor!
			we ant is the call to destructor should be generated based
			on the type of the object that the account pointer is pointing at.
			For this reason, we have to make "destructor of the base class virtual".
			*/
#ifdef _BANKING_DEBUG
			std::clog << __FUNCSIG__ << '\n';
#endif // _BANKING_DEBUG

			/*
			 * Without virtual destructor
			...bla bla bla
			<missing ~Savings>
			Banking::Account::~Account(void)
			 * With virtual destructor
			...bla bla bla
			Banking::Savings::~Savings(void)
			Banking::Account::~Account(void)
			*/
			Account* acc = new Savings("Mustafa_Account_Savings", 100, 0.8f);
			//Transact(acc);
			delete acc;
		}
		void Transact_TEST_main() {
			Transact_TEST_Account();
			Transact_TEST_Checking();
			Transact_TEST_Savings();
			Transact_TEST_destructor();
		}
	};
}