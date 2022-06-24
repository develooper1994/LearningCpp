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
	//void Transact_pointer(Checking* account);
	void Transact(Account* account);
	void Transact(Account& account);

	struct Transact_TEST {

		// pointer
		// It was giving wrong minimum balance info due to object-slicing so that i check to don't give any wrong info at all
		/*
			-*-*-*-*-* Transact_TEST_pointer *-*-*-*-*-

			void __cdecl Banking::Transact_TEST::Transact_TEST_Account_pointer(void)
			Transaction started
			Initial balance:100
			Interest rate:0
			Final balance:30
			void __cdecl Banking::Transact_TEST::Transact_TEST_Checking_pointer(void)
			Transaction started
			Initial balance:100
			Minimum balance of checking:50
			Interest rate:0
			Final balance:30
			void __cdecl Banking::Transact_TEST::Transact_TEST_Savings_pointer(void)
			Transaction started
			Initial balance:100
			Interest rate:0.8
			Final balance:190
			void __cdecl Banking::Transact_TEST::Transact_TEST_destructor_pointer(void)
			Transaction started
			Initial balance:100
			Interest rate:0.8
			Final balance:190
		*/
		inline void Transact_TEST_Account_pointer() {
#ifdef _BANKING_DEBUG
			std::clog << __FUNCSIG__ << '\n';
#endif // _BANKING_DEBUG
			Account acc("Mustafa_Account", 100); // minimum balance is not attribute of Account class so it didn't set! 
			Transact(&acc);
		}
		inline void Transact_TEST_Checking_pointer() {
#ifdef _BANKING_DEBUG
			std::clog << __FUNCSIG__ << '\n';
#endif // _BANKING_DEBUG
			Checking ch("Mustafa_Checking", 100, 50);
			Transact(&ch);
		}
		inline void Transact_TEST_Savings_pointer() {
#ifdef _BANKING_DEBUG
			std::clog << __FUNCSIG__ << '\n';
#endif // _BANKING_DEBUG
			Savings save("Mustafa_Savings", 100, 0.8f); // very attractive interest :]
			Transact(&save);
		}
		inline void Transact_TEST_destructor_pointer() {
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
			Transact(acc);
			delete acc;
		}
		void Transact_TEST_pointer_main() {
			Transact_TEST_Account_pointer();
			Transact_TEST_Checking_pointer();
			Transact_TEST_Savings_pointer();
			Transact_TEST_destructor_pointer();
		}

		// reference
		// throws exception when wrong class comes to the class!
		/*
			-*-*-*-*-* Transact_TEST_pointer *-*-*-*-*-

			void __cdecl Banking::Transact_TEST::Transact_TEST_Account_reference(void)
			Transaction started
			Initial balance:100
			Exception:Bad dynamic_cast!
			void __cdecl Banking::Transact_TEST::Transact_TEST_Checking_reference(void)
			Transaction started
			Initial balance:100
			Minimum balance of checking:50
			Interest rate:0
			Final balance:30
			void __cdecl Banking::Transact_TEST::Transact_TEST_Savings_reference(void)
			Transaction started
			Initial balance:100
			Exception:Bad dynamic_cast!
		*/
		inline void Transact_TEST_Account_reference() {
#ifdef _BANKING_DEBUG
			std::clog << __FUNCSIG__ << '\n';
#endif // _BANKING_DEBUG
			Account acc("Mustafa_Account", 100); // minimum balance is not attribute of Account class so it didn't set! 
			try {
				Transact(acc);
			}
			catch (const std::exception& ex) {
				std::cout << "Exception:" << ex.what() << '\n';
			}
		}
		inline void Transact_TEST_Checking_reference() {
#ifdef _BANKING_DEBUG
			std::clog << __FUNCSIG__ << '\n';
#endif // _BANKING_DEBUG
			Checking ch("Mustafa_Checking", 100, 50);
			try {
				Transact(ch);
			}
			catch (const std::exception& ex) {
				std::cout << "Exception:" << ex.what() << '\n';
			}
		}
		inline void Transact_TEST_Savings_reference() {
#ifdef _BANKING_DEBUG
			std::clog << __FUNCSIG__ << '\n';
#endif // _BANKING_DEBUG
			Savings save("Mustafa_Savings", 100, 0.8f); // very attractive interest :]
			try {
				Transact(save);
			}
			catch (const std::exception& ex) {
				std::cout << "Exception:" << ex.what() << '\n';
			}
		}
		void Transact_TEST_reference_main() {
			Transact_TEST_Account_reference();
			Transact_TEST_Checking_reference();
			Transact_TEST_Savings_reference();
		}

	};
}







/*

-*-*-*-*-* Transact_TEST_pointer *-*-*-*-*-

void __cdecl Banking::Transact_TEST::Transact_TEST_Account_pointer(void)
__cdecl Banking::Account::Account(const class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > &,float)
void __cdecl Banking::Transact(class Banking::Account *)
Transaction started
Initial balance:float __cdecl Banking::Account::GetBalance(void) const
100
void __cdecl Banking::Account::Deposit(float)
void __cdecl Banking::Account::AccumulateInterest(void)
Interest rate:float __cdecl Banking::Account::GetInterestRate(void) const
0
Final balance:float __cdecl Banking::Account::GetBalance(void) const
30
__cdecl Banking::Account::~Account(void)
void __cdecl Banking::Transact_TEST::Transact_TEST_Checking_pointer(void)
__cdecl Banking::Account::Account(const class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > &,float)
__cdecl Banking::Checking::Checking(const class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > &,float,float)
void __cdecl Banking::Transact(class Banking::Account *)
Transaction started
Initial balance:float __cdecl Banking::Account::GetBalance(void) const
100
void __cdecl Banking::Account::Deposit(float)
void __cdecl Banking::Account::AccumulateInterest(void)
Minimum balance of checking:50
Interest rate:float __cdecl Banking::Account::GetInterestRate(void) const
0
Final balance:float __cdecl Banking::Account::GetBalance(void) const
30
__cdecl Banking::Checking::~Checking(void)
__cdecl Banking::Account::~Account(void)
void __cdecl Banking::Transact_TEST::Transact_TEST_Savings_pointer(void)
__cdecl Banking::Account::Account(const class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > &,float)
__cdecl Banking::Savings::Savings(const class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > &,float,float)
void __cdecl Banking::Transact(class Banking::Account *)
Transaction started
Initial balance:float __cdecl Banking::Account::GetBalance(void) const
100
void __cdecl Banking::Account::Deposit(float)
void __cdecl Banking::Savings::AccumulateInterest(void)
Interest rate:float __cdecl Banking::Savings::GetInterestRate(void) const
0.8
Final balance:float __cdecl Banking::Account::GetBalance(void) const
190
__cdecl Banking::Savings::~Savings(void)
__cdecl Banking::Account::~Account(void)
void __cdecl Banking::Transact_TEST::Transact_TEST_destructor_pointer(void)
__cdecl Banking::Account::Account(const class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > &,float)
__cdecl Banking::Savings::Savings(const class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > &,float,float)
void __cdecl Banking::Transact(class Banking::Account *)
Transaction started
Initial balance:float __cdecl Banking::Account::GetBalance(void) const
100
void __cdecl Banking::Account::Deposit(float)
void __cdecl Banking::Savings::AccumulateInterest(void)
Interest rate:float __cdecl Banking::Savings::GetInterestRate(void) const
0.8
Final balance:float __cdecl Banking::Account::GetBalance(void) const
190
__cdecl Banking::Savings::~Savings(void)
__cdecl Banking::Account::~Account(void)

-*-*-*-*-* Transact_TEST_pointer *-*-*-*-*-

void __cdecl Banking::Transact_TEST::Transact_TEST_Account_reference(void)
__cdecl Banking::Account::Account(const class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > &,float)
void __cdecl Banking::Transact(class Banking::Account &)
Transaction started
Initial balance:float __cdecl Banking::Account::GetBalance(void) const
100
void __cdecl Banking::Account::Deposit(float)
void __cdecl Banking::Account::AccumulateInterest(void)
Exception:Bad dynamic_cast!
__cdecl Banking::Account::~Account(void)
void __cdecl Banking::Transact_TEST::Transact_TEST_Checking_reference(void)
__cdecl Banking::Account::Account(const class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > &,float)
__cdecl Banking::Checking::Checking(const class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > &,float,float)
void __cdecl Banking::Transact(class Banking::Account &)
Transaction started
Initial balance:float __cdecl Banking::Account::GetBalance(void) const
100
void __cdecl Banking::Account::Deposit(float)
void __cdecl Banking::Account::AccumulateInterest(void)
Minimum balance of checking:50
Interest rate:float __cdecl Banking::Account::GetInterestRate(void) const
0
Final balance:float __cdecl Banking::Account::GetBalance(void) const
30
__cdecl Banking::Checking::~Checking(void)
__cdecl Banking::Account::~Account(void)
void __cdecl Banking::Transact_TEST::Transact_TEST_Savings_reference(void)
__cdecl Banking::Account::Account(const class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > &,float)
__cdecl Banking::Savings::Savings(const class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > &,float,float)
void __cdecl Banking::Transact(class Banking::Account &)
Transaction started
Initial balance:float __cdecl Banking::Account::GetBalance(void) const
100
void __cdecl Banking::Account::Deposit(float)
void __cdecl Banking::Savings::AccumulateInterest(void)
Exception:Bad dynamic_cast!
__cdecl Banking::Savings::~Savings(void)
__cdecl Banking::Account::~Account(void)


*/





